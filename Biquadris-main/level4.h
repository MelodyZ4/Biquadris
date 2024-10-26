#ifndef __LEVEL_4_H__
#define __LEVEL_4_H__
#include <vector>

#include "level.h"

class Level4 : public Level {
  std::vector<char> sequence;
  int numplaced = 0;

 public:
  Level4();
  Level4(const std::string &s);
  int getsingle();
  void placedone();
  void resetsingle();
  unique_ptr<Block> createBlock(int blockId) override;
};

#endif
