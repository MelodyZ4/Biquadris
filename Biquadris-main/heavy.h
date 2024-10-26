#ifndef __HEAVY_H__
#define __HEAVY_H__
#include "decorator.h"
#include <string>
using namespace std;

class Heavy : public Decorator {
   public:
    Heavy(std::unique_ptr<Board> component);
    std::vector<std::vector<char>> getBoard() override;
    Block *getCurrBlock() override;
    bool moveBlock(string s) override;
};

#endif

