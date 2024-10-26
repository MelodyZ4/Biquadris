#ifndef __BOARDBASE_H__
#define __BOARDBASE_H__
#include <memory>
#include <unordered_map>
#include <vector>

#include "board.h"
#include "cell.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

class BoardBase : public Board {
  int currLevel = 0;
  int score = 0;
  bool isLost = false;
  int hiScore = 0;
  std::vector<std::vector<Cell>> grid;
  std::unique_ptr<Block> currBlock;
  std::unique_ptr<Block> nextBlock;
  std::string sourceFile;  // file for input
  std::unique_ptr<Level> level;

  int blocksCreated = 0;
  std::unordered_map<int, std::pair<int, int>>
      blocks;  // blockId, <numOfCellsRemaining, levelGenerated>

  void moveDown(int row);
  int clearRow();

 public:
  BoardBase();
  int getHiScore() const override;
  bool blockPlaceable(char block) override;
  int getCurrLevel() const override;
  int getCurrScore() const override;
  bool ifLost() const override;
  Cell &getCell(int x, int y) override;
  Level *getLevel() override;
  Block *getCurrBlock() override;
  Block *getNextBlock() override;
  void setCurrBlock(std::unique_ptr<Block> b) override;
  void setNextBlock(std::unique_ptr<Block> b) override;
  std::vector<std::vector<char>> getBoard() override;
  void setCurrentLevel(int n) override;
  void setSourceFile(const std::string &filename) override;
  void turnRandomOff(const std::vector<char> &sequence) override;
  void turnRandomOn() override;
  bool moveBlock(
      std::string s) override;  // returns true if should drop else false

  void init() override;
  void reset() override;

  int update() override;  // Update to prepare for "next turn"

  void forceCurrBlock(char c) override;
  std::unique_ptr<Board> getBaseBoard() override;
};

#endif

// #ifndef __BOARDBASE_H__
// #define __BOARDBASE_H__
// #include <vector>
// #include <memory>
// #include "board.h"
// #include "cell.h"
// #include "level0.h"
// #include "level1.h"
// #include "level2.h"
// #include "level3.h"
// #include "level4.h"

// class BoardBase : public Board {
//     int currLevel = 0;
//     int score = 0;
//     bool isLost = false;
//     std::vector<std::vector<Cell>> grid;
//     std::unique_ptr<Block> currBlock;
//     std::unique_ptr<Block> nextBlock;
//     std::string sourceFile;                       // file for input
//     std::unique_ptr<Level> level;

//     void moveDown(int row);
//     int clearRow();

//   public:
//     BoardBase();

//     int getCurrLevel() const override;
//     int getCurrScore() const override;
//     bool ifLost() const override;
//     Cell &getCell(int x, int y) override;
//     Level *getLevel() override;
//     Block *getCurrBlock() override;
//     Block *getNextBlock() override;
//     void setCurrBlock(std::unique_ptr<Block> b) override;
//     void setNextBlock(std::unique_ptr<Block> b) override;
//     std::vector<std::vector<char>> getBoard() override;
//     void setCurrentLevel(int n) override;
//     void setSourceFile(const std::string &filename) override;
//     void turnRandomOff(const std::string &file);
//     void turnRandomOn();
//     void moveBlock(std::string s) override;

//     void init() override;
//     void reset() override;

//     int update() override;          // Update to prepare for "next turn"

// };

// #endif
