 #include "heavy.h"
 #include "block.h"
 
Heavy::Heavy(std::unique_ptr<Board> component): Decorator{std::move(component)} {}

Block* Heavy::getCurrBlock(){
    return component->getCurrBlock();
}

std::vector<std::vector<char>> Heavy::getBoard(){
    return component->getBoard();
}

bool Heavy::moveBlock(string s){
    if(s=="right"){
        //Block* b=component->getCurrBlock();
        
        component->moveBlock("right");
        component->moveBlock("heavyDown");
        
    }
    else if(s=="left"){
        //Block* b=component->getCurrBlock();
        component->moveBlock("left");
        component->moveBlock("heavyDown");
    }
    else{
        component->moveBlock(s);
    }
    return false;
}

