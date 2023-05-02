# Console Toolkit
A basic toolkit for manipulating a Windows console window's buffer size, window size and colour settings.
___
### Brief function overview
- ```ColourPicker(background, text)``` takes two ints between 0 and 15 (selection listed below) and produces a colour ID between 0 and 255.

- ```SetActiveColour(colour)``` sets the active print colour to the returned value mentioned above.

- ```SetColourValue(index, hexColour)``` sets a new hex value as the colour at a given index (selection listed below).

- ```ApplyConsoleColours()``` must be called after any changes made to colour values.

- ```ResetColourValue(index)``` resets the colour value at a given index to its value when the class object was first instantiated.

- ```RevertConsoleColours()``` reapplies all original colour values. Should usually be called before exit.

- ```GotoXY(x, y)``` sets the cursor position.

Regarding window size changes, make sure the window size is set no larger than the buffer size, or the change will silently fail. The buffer, however, can safely be set smaller than the window.

Everything else should be relatively self-explanatory.
___
### Standard Colour scheme

0 Black *(background by default)*  
1 Dark Blue  
2 Dark Green  
3 Dark Cyan  
4 Dark Red  
5 Dark Magenta  
6 Dark Yellow  
7 Bright Grey *(text colour by default)*  
8 Dark Grey  
9 Bright Blue  
10 Bright Green  
11 Bright Cyan  
12 Bright Red  
13 Bright Magenta  
14 Bright Yellow  
15 White
