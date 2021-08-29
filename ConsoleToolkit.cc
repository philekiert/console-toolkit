/* Standard Colour scheme
-------------------------
0 Black            Background
1 Dark Blue
2 Dark Green
3 Dark Cyan
4 Dark Red
5 Dark Magenta
6 Dark Yellow
7 Bright Grey      Foreground (text)
8 Dark Grey
9 Bright Blue
10 Bright Green
11 Bright Cyan
12 Bright Red
13 Bright Magenta
14 Bright Yellow
15 White                          */

#include <windows.h>
#include <conio.h>
#include "ConsoleToolkit.hpp"

ConsoleToolkit::ConsoleToolkit():
window(GetConsoleWindow()), // Get the handle for the window.
outputBuff(GetStdHandle(-11)) /* -11 here gets the output buffer.
                                 -10 would be input buffer, -12 would be error buffer. */
{
  bufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
  GetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
  
  // Console buffer size in bytes.
  bufferInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

  // Store the current colour scheme.
  for (size_t n = 0; n < 16; ++n)
    oldColourTable[n] = bufferInfo.ColorTable[n];

  // Store the currently active colour.
  oldColourSelection = bufferInfo.wAttributes;

  // Store the current buffer size.
  oldBufferSize[0] = bufferInfo.dwSize.X;
  oldBufferSize[1] = bufferInfo.dwSize.Y;
}

unsigned ConsoleToolkit::ColourPicker(const unsigned &back, const unsigned &fore) const
{
  return back * 16 + fore;
}

void ConsoleToolkit::SetActiveColour(const unsigned &col)
{
  SetConsoleTextAttribute(outputBuff, col);
  GetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
}

void ConsoleToolkit::SetColourValue(const size_t &index, const COLORREF &hexColour)
{
  bufferInfo.ColorTable[index] = hexColour;
}
void ConsoleToolkit::ResetColourValue(const size_t &index)
{
  bufferInfo.ColorTable[index] = oldColourTable[index];
}

void ConsoleToolkit::ApplyConsoleColours()
{
  SetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
}

void ConsoleToolkit::RevertConsoleColours()
{
  for (size_t n = 0; n < 16; ++n)
    bufferInfo.ColorTable[n] = oldColourTable[n];
  bufferInfo.wAttributes = oldColourSelection;
  SetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
}


// Other Useful Tools
// ------------------

void ConsoleToolkit::SetConsoleWindowSize(const short &x, const short &y)
{
  SMALL_RECT win{0, 0, x - 1, y - 1};
  SetConsoleWindowInfo(outputBuff, true, &win);
}
void ConsoleToolkit::SetConsoleBufferSize(const short &x, const short &y)
{
  bufferInfo.dwSize.X = x;
  bufferInfo.dwSize.Y = y;

  SetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
}
void ConsoleToolkit::RevertConsoleBufferSize()
{
  bufferInfo.dwSize.X = oldBufferSize[0];
  bufferInfo.dwSize.Y = oldBufferSize[1];

  SetConsoleScreenBufferInfoEx(outputBuff, &bufferInfo);
}


void ConsoleToolkit::SetConsoleNotResizable(const bool &choice)
{
  if (choice)
  {
    SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_SIZEBOX);
    SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
  }
  else
  {
    SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) | WS_SIZEBOX);
    SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
  }
}
void ConsoleToolkit::DisableConsoleMaximise()
{
  SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_MAXIMIZEBOX);
  SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
void ConsoleToolkit::EnableConsoleMaximise()
{
  SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) | WS_MAXIMIZEBOX);
  SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
void ConsoleToolkit::DisableConsoleMinimise()
{
  SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_MINIMIZEBOX);
  SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
void ConsoleToolkit::EnableConsoleMinimise()
{
  SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) | WS_MINIMIZEBOX);
  SetWindowPos(window, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void ConsoleToolkit::ShowCursor(const bool &sc)
{
  CONSOLE_CURSOR_INFO cursorInf;
  GetConsoleCursorInfo(outputBuff, &cursorInf);
  if (sc) cursorInf.bVisible = true;
  else cursorInf.bVisible = false;
  SetConsoleCursorInfo(outputBuff, &cursorInf);
}

void ConsoleToolkit::GotoXY(const short &x, const short &y)
{
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

  lastX = x;
  lastY = y;
}
