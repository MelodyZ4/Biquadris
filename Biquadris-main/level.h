#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <memory>
#include <vector>

#include "block.h"

class Level {
  int level;

 protected:
  void setisRandom(bool rand);
  bool getRandom();

 protected:
  bool isRandom = false;
  int noRandomCount = 0;
  std::vector<char> noRandomSequence;

 public:
  Level(int level);
  virtual ~Level();
  int getLevel() const;

  virtual std::unique_ptr<Block> createBlock(int blockId) = 0;
  std::unique_ptr<Block> createBlock(char c, int blockId, bool heavy = false);
  virtual void turnOnRandom();
  virtual void turnOffRandom(const std::vector<char> &sequence);
};

#endif
