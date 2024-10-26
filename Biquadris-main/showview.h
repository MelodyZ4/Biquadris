#ifndef __SHOWVIEW_H__
#define __SHOWVIEW_H__
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "controller.h"
#include "graphicsdisplay.h"
#include "observer.h"
#include "textview.h"

class BiquadrisView : public Observer {
  BiquadrisModel *model;
  BiquadrisController *controller;

  bool graphics;
  std::unique_ptr<TextView> td;      // for text
  std::unique_ptr<GraphicsView> gd;  // for graphic(xwindow)

 public:
  BiquadrisView(BiquadrisModel *m, BiquadrisController *c,
                bool graphics = true);
  virtual ~BiquadrisView();
  virtual void update();  // Observer Pattern: concrete update() method
  void getCommand();
  void getCommand(const std::string &filename);
  //   void nextCommand(const std::string &cmd);
  void runCmd(const std::string &cmd);

  // std::pair<int, std::string> parseCommand(const std::string &cmd);
};

#endif
