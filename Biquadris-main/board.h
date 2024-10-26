#ifndef __BOARD_H__
#define __BOARD_H__
#include <memory>
#include <string>
#include <vector>

const int ROWS = 18;
const int COLS = 11;

class Block;
class Level;
class Cell;

class Board {
 public:
  virtual ~Board();

  virtual bool blockPlaceable(char block) = 0;
  virtual std::vector<std::vector<char>> getBoard() = 0;
  virtual Level *getLevel() = 0;
  virtual int getCurrLevel() const = 0;
  virtual int getHiScore() const = 0;
  virtual int getCurrScore() const = 0;
  virtual Block *getCurrBlock() = 0;
  virtual Block *getNextBlock() = 0;
  virtual void setCurrBlock(std::unique_ptr<Block> b) = 0;
  virtual void setNextBlock(std::unique_ptr<Block> b) = 0;
  virtual Cell &getCell(int x, int y) = 0;
  virtual bool ifLost() const = 0;
  virtual void setCurrentLevel(int n) = 0;
  virtual void setSourceFile(const std::string &filename) = 0;
  virtual bool moveBlock(std::string s) = 0;
  virtual void init() = 0;
  virtual void reset() = 0;
  virtual int update() = 0;
  virtual void forceCurrBlock(char c) = 0;

  virtual void turnRandomOff(const std::vector<char> &sequence) = 0;
  virtual void turnRandomOn() = 0;

  virtual std::unique_ptr<Board> getBaseBoard() = 0;
};

#endif
