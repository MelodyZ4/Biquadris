#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__
#include <vector>

#include "level.h"

class Level3 : public Level {
  std::vector<char> sequence;

 public:
  Level3();
  unique_ptr<Block> createBlock(int blockId) override;
};

#endif
