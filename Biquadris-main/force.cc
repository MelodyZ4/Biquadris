#include "force.h"
using namespace std;

Force::Force(std::unique_ptr<Board> component) : Decorator{std::move(component)} {}

std::vector<std::vector<char>> Force::getBoard(){ 
    return component->getBoard(); 
}

bool Force::moveBlock(string s) { 
    return component->moveBlock(s); }

