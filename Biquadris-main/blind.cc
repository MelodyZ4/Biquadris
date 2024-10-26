 #include "blind.h"
 #include "block.h"
 
Blind::Blind(std::unique_ptr<Board> component): Decorator{std::move(component)} {}

Block* Blind::getCurrBlock(){
    return component->getCurrBlock();
}

std::vector<std::vector<char>> Blind::getBoard(){
    std::vector<std::vector<char>> board = component->getBoard();
    for (int r = 2; r < 12; r++)
        for (int c = 2; c < 9; c++) board[r][c] = '?';
    return board;
}

bool Blind::moveBlock(string s){
    return component->moveBlock(s);
}
