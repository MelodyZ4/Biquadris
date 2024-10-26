#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include <memory>

#include "block.h"
#include "board.h"
#include "level.h"

class Decorator : public Board {
 protected:
  std::unique_ptr<Board> component;

 public:
  Decorator(std::unique_ptr<Board> component);
  virtual ~Decorator();

  bool blockPlaceable(char block);
  std::vector<std::vector<char>> getBoard();
  Level *getLevel();
  int getCurrLevel() const;
  int getHiScore() const;
  int getCurrScore() const;
  Block *getCurrBlock();
  Block *getNextBlock();
  void setCurrBlock(std::unique_ptr<Block> b);
  void setNextBlock(std::unique_ptr<Block> b);
  Cell &getCell(int x, int y);
  bool ifLost() const;
  void setCurrentLevel(int n);
  void setSourceFile(const std::string &filename);
  bool moveBlock(std::string s);
  void init();
  void reset();
  int update();

  void turnRandomOff(const std::vector<char> &sequence);
  void turnRandomOn();

  void forceCurrBlock(char c) override;
  std::unique_ptr<Board> getBaseBoard() override;
};

#endif
