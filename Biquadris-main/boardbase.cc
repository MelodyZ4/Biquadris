#include "boardbase.h"

#include <fstream>

#include "block.h"
#include "cell.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;

BoardBase::BoardBase() {}

void BoardBase::init() {
  int row = 18;
  int col = 11;
  for (int r = 0; r < row; ++r) {
    grid.emplace_back();
    for (int c = 0; c < col; ++c) {
      grid[r].emplace_back(0, 0, '_');
      grid[r][c].setCoords(17 - r, c);
    }
  }

  // SHOULD NOT SET THIS AGAIN. THIS IS SET IN main.cc WHEN INITIALIZED.
  // need to change the level, level 1 for testing
  // this->setCurrentLevel(4);

  // confusion why does createBlock()->get() get the same address

  // create current block
  std::unique_ptr<Block> curr = level->createBlock(blocksCreated);
  blocks[blocksCreated++] = std::make_pair(4, level->getLevel());
  this->setCurrBlock(std::move(curr));

  // for(int i=0;i<4;i++){
  //     cout<<currBlock.get()->getposition()[i].getChar()<<'
  //     '<<currBlock.get()->getposition()[i].getCol()<<'
  //     '<<currBlock.get()->getposition()[i].getRow()<<'\n';
  // }
  // cout<<this->getCurrBlock()->getChar()<<'\n';

  // create next block
  std::unique_ptr<Block> next = level->createBlock(blocksCreated);
  blocks[blocksCreated++] = std::make_pair(4, level->getLevel());
  this->setNextBlock(std::move(next));
  // cout<<curr.get()<<next.get()<<'\n';
}

bool BoardBase::blockPlaceable(char block) {
  vector<Cell> v;
  int top = 0;
  int left = 0;
  int bottom = 0;
  int right = 0;
  if (block == '*') {
    Cell c1(0, 0, '*', 0);
    v.emplace_back(c1);
    top = 14;
    left = 5;
    bottom = 14;
    right = 5;

  }

  else if (block == 'Z') {
    Cell c1(1, 0, 'Z', 0);
    Cell c2(1, 1, 'Z', 0);
    Cell c3(0, 1, 'Z', 0);
    Cell c4(0, 2, 'Z', 0);
    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);

    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (block == 'S') {
    Cell c1(0, 0, 'S', 0);
    Cell c2(0, 1, 'S', 0);
    Cell c3(1, 1, 'S', 0);
    Cell c4(1, 2, 'S', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (block == 'O') {
    Cell c1(0, 0, 'O', 0);
    Cell c2(0, 1, 'O', 0);
    Cell c3(1, 0, 'O', 0);
    Cell c4(1, 1, 'O', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 15;
    left = 0;
    bottom = 14;
    right = 1;

  } else if (block == 'T') {
    Cell c1(1, 0, 'T', 0);
    Cell c2(1, 1, 'T', 0);
    Cell c3(1, 2, 'T', 0);
    Cell c4(0, 1, 'T', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (block == 'L') {
    Cell c1(0, 0, 'L', 0);
    Cell c2(0, 1, 'L', 0);
    Cell c3(0, 2, 'L', 0);
    Cell c4(1, 2, 'L', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (block == 'J') {
    Cell c1(0, 0, 'J', 0);
    Cell c2(0, 1, 'J', 0);
    Cell c3(0, 2, 'J', 0);
    Cell c4(1, 0, 'J', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else {  // (type == 'I')

    Cell c1(0, 0, 'I', 0);
    Cell c2(0, 1, 'I', 0);
    Cell c3(0, 2, 'I', 0);
    Cell c4(0, 3, 'I', 0);

    v.emplace_back(c1);
    v.emplace_back(c2);
    v.emplace_back(c3);
    v.emplace_back(c4);
    top = 14;
    left = 0;
    bottom = 14;
    right = 3;
  }
  for (int i = 0; i < (int)v.size(); i++) {
    if (grid[17 - (v[i].getRow() + bottom)][v[i].getCol() + left].getChar() !=
        '_') {
      return false;
    }
  }
  return true;
}

int BoardBase::getHiScore() const { return hiScore; }

int BoardBase::getCurrLevel() const { return currLevel; }

int BoardBase::getCurrScore() const { return score; }

bool BoardBase::ifLost() const { return isLost; }

Cell &BoardBase::getCell(int x, int y) { return grid[x][y]; }

Level *BoardBase::getLevel() { return this->level.get(); }

Block *BoardBase::getCurrBlock() { return currBlock.get(); }

Block *BoardBase::getNextBlock() { return nextBlock.get(); }

void BoardBase::setCurrBlock(std::unique_ptr<Block> b) {
  currBlock = std::move(b);
}

void BoardBase::setNextBlock(std::unique_ptr<Block> b) {
  nextBlock = std::move(b);
}

std::vector<std::vector<char>> BoardBase::getBoard() {
  std::vector<std::vector<char>> theBoard;
  for (int r = 0; r < 18; ++r) {
    theBoard.emplace_back();
    for (int c = 0; c < 11; ++c) theBoard[r].emplace_back(grid[r][c].getChar());
  }

  // using this->getCurrBlock()->getposition() to get the current block
  // vector<Cell>, seem like we can't let vector equal to vector?

  int base_row = this->getCurrBlock()->getBottom();
  int base_col = this->getCurrBlock()->getLeft();
  // cout<<this->getCurrBlock()->getChar()<<'\n';
  if (ifLost()) {
    return theBoard;
  }

  // update curr block
  for (int i = 0; i < 4; ++i) {
    // cout<<17-(this->getCurrBlock()->v[i].getRow()+base_row)<<'
    // '<<base_col+this->getCurrBlock()->v[i].getCol()<<'
    // '<<this->getCurrBlock()->v[i].getChar()<<'\n';
    theBoard[17 - (this->getCurrBlock()->getposition()[i].getRow() + base_row)]
            [base_col + this->getCurrBlock()->getposition()[i].getCol()] =
                this->getCurrBlock()->getposition()[i].getChar();
  }

  return theBoard;
}

void BoardBase::setSourceFile(const std::string &filename) {
  sourceFile = filename;
}

void BoardBase::setCurrentLevel(int n) {
  if (n < 0 or n > 4) return;
  currLevel = n;
  if (n == 0) {
    level = make_unique<Level0>(sourceFile);
  } else if (n == 1) {
    level = make_unique<Level1>();
  } else if (n == 2) {
    level = make_unique<Level2>();
  } else if (n == 3) {
    level = make_unique<Level3>();
  } else if (n == 4) {
    level = make_unique<Level4>();
  }
}

void BoardBase::moveDown(int row) {
  // if it's the highest row then we don't move down
  if (row == 0) {
    for (int c = 0; c < 18; ++c) {
      grid[row][c].setChar('_');
    }
    return;
  }

  for (int i = row; i > 0; --i) {
    for (int j = 0; j < 11; ++j) {
      grid[i][j] = grid[i - 1][j];
    }
  }
}

int BoardBase::clearRow() {
  int linesClear = 0;

  // In progress
  // for (int i = 0; i < 18; ++i)  { // 0 <= i <= 17
  //     bool isCompleteRow = true;
  //     for (int j = 0; j < 11 && isCompleteRow; ++j) {
  //         if (grid[i][j].getChar() == '_') {
  //             isCompleteRow = false;
  //         }
  //     }
  //    // else isCompleteRow
  //         /* clearRow */
  //     if (isCompleteRow) {
  //         for (int j = 0; j < 11; ++j) {
  //             grid[i][j].setChar(grid[i - 1][j].getChar());
  //         }
  //     }
  // }

  vector<int> rem_row;
  for (int r = 0; r < 18; r++) {
    int cnt = 0;
    for (int c = 0; c < 11; c++) {
      if (grid[r][c].getChar() != '_') {
        cnt += 1;
      } else {
        break;
      }
    }
    if (cnt == 11) {
      linesClear += 1;
      // iterate every cell in that row, and decrement blocks[cell.getBlockId()]
      // -= 1;
      for (int c = 0; c < 11; c++) {
        --blocks[grid[r][c].getBlockId()].first;
        if (blocks[grid[r][c].getBlockId()].first == 0) {
          score += ((blocks[grid[r][c].getBlockId()].second + 1) *
                    (blocks[grid[r][c].getBlockId()].second + 1));
        }
      }
      rem_row.push_back(r);
    }
  }
  for (int i = 0; i < (int)rem_row.size(); i++) {
    moveDown(rem_row[i]);
    //<<rem_row[i]<<'\n';
  }

  if (linesClear > 0) {
    score +=
        ((level->getLevel() + linesClear) * (level->getLevel() + linesClear));
  }
  if (score > hiScore) hiScore = score;

  return linesClear;
}

int BoardBase::update() {
  int base_row = this->getCurrBlock()->getBottom();
  int base_col = this->getCurrBlock()->getLeft();

  for (int i = 0; i < (int)this->getCurrBlock()->getposition().size(); ++i) {
    // cout<<17-(this->getCurrBlock()->v[i].getRow()+base_row)<<'
    // '<<base_col+this->getCurrBlock()->v[i].getCol()<<'
    // '<<this->getCurrBlock()->v[i].getChar()<<'\n';
    grid[17 - (this->getCurrBlock()->getposition()[i].getRow() + base_row)]
        [base_col + this->getCurrBlock()->getposition()[i].getCol()] =
            Cell(this->getCurrBlock()->getposition()[i].getRow(),
                 this->getCurrBlock()->getposition()[i].getCol(),
                 this->getCurrBlock()->getposition()[i].getChar(),
                 getCurrBlock()->getBlockId());
  }

  int linesCleared = 0;
  linesCleared += clearRow();

  if (currLevel == 4) {
    auto level4 = dynamic_cast<Level4 *>(level.get());
    level4->placedone();

    if (linesCleared <= 0 && level4->getsingle() % 5 == 0 &&
        level4->getsingle() > 0) {
      // reset
      // create a star block
      std::unique_ptr<Block> starBlock =
          level->createBlock('*', blocksCreated, true);
      blocks[blocksCreated++] = std::make_pair(1, level->getLevel());

      // should set currBlock to a new star block, and not modify nextBlock
      this->setCurrBlock(std::move(starBlock));
      if (!blockPlaceable(currBlock->getChar())) {
        isLost = true;
      } else {
        // drop on that currBlock
        currBlock->drop(grid);

        // update
        base_row = this->getCurrBlock()->getBottom();
        base_col = this->getCurrBlock()->getLeft();
        // cout << base_row << " " << base_col << std::endl;
        grid[17 - (this->getCurrBlock()->getposition()[0].getRow() + base_row)]
            [base_col + this->getCurrBlock()->getposition()[0].getCol()] =
                Cell(this->getCurrBlock()->getposition()[0].getRow(),
                     this->getCurrBlock()->getposition()[0].getCol(),
                     this->getCurrBlock()->getposition()[0].getChar(),
                     getCurrBlock()->getBlockId());
        linesCleared += clearRow();
      }
    }

    if (linesCleared > 0) {
      level4->resetsingle();
    }
  }

  // Update currBlock
  this->setCurrBlock(std::move(nextBlock));
  // currBlock = nextBlock;

  // check if the game is finished
  //! blockPlaceable(currBlock->getChar())
  if (!blockPlaceable(currBlock->getChar())) {
    isLost = true;
  }

  // create nextBlock
  std::unique_ptr<Block> temp = level->createBlock(blocksCreated);
  blocks[blocksCreated++] = std::make_pair(4, level->getLevel());
  this->setNextBlock(std::move(temp));
  return linesCleared;
}

void BoardBase::reset() {
  grid.clear();
  // currBlock = nullptr;
  // nextBlock = nullptr;
  currLevel = 0;
  score = 0;
  init();
}

void BoardBase::turnRandomOff(const std::vector<char> &sequence) {
  if (currLevel != 3 and currLevel != 4) return;

  level->turnOffRandom(sequence);
}

void BoardBase::turnRandomOn() {
  if (currLevel != 3 and currLevel != 4) return;
  level->turnOnRandom();
}

bool BoardBase::moveBlock(string s) {
  if (s == "left") {
    currBlock->moveLeft(grid);
  } else if (s == "right") {
    currBlock->moveRight(grid);
  } else if (s == "down") {
    currBlock->moveDown(grid);
  } else if (s == "drop") {
    currBlock->drop(grid);
    // int base_row = this->getCurrBlock()->getBottom();
    // int base_col = this->getCurrBlock()->getLeft();
    // for(int i = 0; i < 4; ++i){
    //     //cout<<17-(this->getCurrBlock()->v[i].getRow()+base_row)<<'
    //     '<<base_col+this->getCurrBlock()->v[i].getCol()<<'
    //     '<<this->getCurrBlock()->v[i].getChar()<<'\n';
    //     grid[17-(this->getCurrBlock()->getposition()[i].getRow()+base_row)]
    //     [base_col+this->getCurrBlock()->getposition()[i].getCol()]
    //     .setChar(this->getCurrBlock()->getposition()[i].getChar());
    // }

    // *********** MOVING THIS TO UPDATE METHOD ABOVE ***********
    // if (currLevel == 4) {
    //     (dynamic_cast<Level4*>(getLevel()))->placedone();
    //     if ((dynamic_cast<Level4*>(getLevel()))->addsingle()) {
    //         int i = 0;
    //         while(i < 18) {
    //             if (grid[17-i][5].getChar() != '_') {
    //                 i += 1;
    //                 continue;
    //             } else {
    //                 grid[17-i][5].setChar('*');
    //             }
    //         }
    //     }
    // }
    return true;
  } else if (s == "cw") {
    currBlock->rotatecw(grid);
  } else if (s == "ccw") {
    currBlock->rotateccw(grid);
  } else if (s == "heavyDown") {
    return currBlock->heavyDown(grid);
  }
  return false;
}

void BoardBase::forceCurrBlock(char c) {
  // create current block
  std::unique_ptr<Block> curr =
      level->createBlock(c, blocksCreated, level->getLevel() >= 3);
  blocks[blocksCreated++] = std::make_pair(4, level->getLevel());
  this->setCurrBlock(std::move(curr));
  if (!blockPlaceable(currBlock->getChar())) {
    isLost = true;
  }
}

std::unique_ptr<Board> BoardBase::getBaseBoard() { return nullptr; }
