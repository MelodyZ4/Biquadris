#ifndef __GRAPHICS_VIEW_H__
#define __GRAPHICS_VIEW_H__
#include <vector>
#include "window.h"

class BiquadrisModel;
class BiquadrisController;

class GraphicsView {
  BiquadrisModel *model;
  BiquadrisController *controller;
  Xwindow w;
  std::vector<std::vector<char>> playerOne;
  std::vector<std::vector<char>> playerTwo;

  void displayNextBlock(char type, int p);

 public:
  GraphicsView(BiquadrisModel *m, BiquadrisController *c);
  ~GraphicsView();
  void displayGame();
};

#endif
