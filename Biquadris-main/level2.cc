#include "level2.h"

#include <random>
#include <vector>

using namespace std;

const static char pieces[7] = {'T', 'S', 'Z', 'O', 'I', 'L', 'J'};

Level2::Level2() : Level{2} {}

unique_ptr<Block> Level2::createBlock(int blockId) {
  //srand((unsigned)time(NULL));
  int random = rand() % 7;
  char c = pieces[random];

  return make_unique<Block>(blockId, c, false);
}
