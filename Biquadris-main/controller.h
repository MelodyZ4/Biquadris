#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>


class BiquadrisModel;

class BiquadrisController {
    BiquadrisModel *model;

    void processSpecialAction();

   public:
    BiquadrisController(BiquadrisModel *m);
    ~BiquadrisController();
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotatecw();
    void rotateccw();
    void drop();
    void levelUp();
    void levelDown();
    void turnRandomOff(const std::string &filename);
    void turnRandomOn();
    void restart();
    void endTurn();
    void swapBlock(char ch);
};

#endif
