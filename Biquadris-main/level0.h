#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__
#include <vector>

#include "level.h"

class Level0 : public Level {
  std::vector<char> sequence;
  int count = 0;

 public:
  Level0(const std::string &s);
  unique_ptr<Block> createBlock(int blockId) override;
};

#endif
