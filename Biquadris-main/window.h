#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>

#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width = 1000,
          int height = 1000);  // Constructor; displays the window.
  ~Xwindow();                  // Destructor; destroys the window.

  enum {
    White = 0,
    Black,
    Cyan,
    Blue,
    Orange,
    Yellow,
    Green,
    Purple,
    Red,
    Brown
  };

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour = Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);
};

#endif
