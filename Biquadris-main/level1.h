#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__
#include "level.h"

class Level1 : public Level {
 public:
  Level1();
  unique_ptr<Block> createBlock(int blockId) override;
};

#endif
