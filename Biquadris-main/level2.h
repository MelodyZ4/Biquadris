#ifndef __LEVEL_2_H__
#define __LEVEL_2_H__
#include <vector>

#include "level.h"

class Level2 : public Level {
 public:
  Level2();
  unique_ptr<Block> createBlock(int blockId) override;
};

#endif
