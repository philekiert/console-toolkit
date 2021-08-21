#ifndef CONSOLE_TOOLKIT_H
#define CONSOLE_TOOLKIT_H

#include <windows.h>

class ConsoleToolkit
{
  const HWND window;
  const HANDLE outputBuff;
  CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo;

  COLORREF oldColourTable[16];
  WORD oldColourSelection;
  short oldBufferSize[2];
  int lastX;
  int lastY;

  public:
  ConsoleToolkit();

  // Colouring
  // ---------

  unsigned ColourPicker(const unsigned &back, const unsigned &fore) const;
  void SetActiveColour(const unsigned &col);

  void SetColourValue(const size_t &index, const COLORREF &hexColour);
  void ResetColourValue(const size_t &index);

  void ApplyConsoleColours();

  void RevertConsoleColours();


  // Other Useful Tools
  // ------------------

  void SetConsoleBufferSize(const short &x, const short &y);
  void RevertConsoleBufferSize();


  void SetConsoleWindowSize(const unsigned &cols, const unsigned &lines);
  void SetConsoleNotResizable();
  void DisableConsoleMaximise();
  void  EnableConsoleMaximise();
  void DisableConsoleMinimise();
  void  EnableConsoleMinimise();

  void ShowCursor(const bool &);

  void GotoXY(const short &x, const short &y);
};

#endif
