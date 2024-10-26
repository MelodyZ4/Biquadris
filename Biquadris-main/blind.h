#ifndef __BLIND_H__
#define __BLIND_H__
#include "decorator.h"
#include <string>
using namespace std;

class Blind : public Decorator {
   public:
    Blind(std::unique_ptr<Board> component);
    std::vector<std::vector<char>> getBoard() override;
    Block *getCurrBlock() override;
    bool moveBlock(string s) override;
};

#endif
