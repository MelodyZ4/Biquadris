#ifndef __TEXT_VIEW_H__
#define __TEXT_VIEW_H__
#include <iostream>
#include <fstream>
#include <vector>
#include "model.h"
#include "observer.h"
#include <string>
class BiquadrisModel;
class BiquadrisController;
const int Row=18;
const int Col=11;

class TextView {
    BiquadrisModel *model;
    BiquadrisController *controller;
    void printNext1(char ch);
    void printNext2(char ch);

    public:
    TextView(BiquadrisModel *m, BiquadrisController *c);
    ~TextView();
    void displayGame();
};

#endif
