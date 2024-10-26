#ifndef __FORCE_H__
#define __FORCE_H__
#include "decorator.h"
#include <string>
using namespace std;

class Force : public Decorator {
   public:
    Force(std::unique_ptr<Board> component);    
     std::vector<std::vector<char>> getBoard() override;
    bool moveBlock(string s) override;
};

#endif

