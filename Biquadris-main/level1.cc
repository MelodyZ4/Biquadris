#include "level1.h"

#include <random>
using namespace std;
const static char pieces[12] = {'T', 'S', 'Z', 'O', 'I', 'L',
                                'J', 'T', 'O', 'I', 'L', 'J'};

Level1::Level1() : Level{1} {}

unique_ptr<Block> Level1::createBlock(int blockId) {
  //srand((unsigned)time(NULL));
  int random = rand() % 12;
  char c = pieces[random];
  return make_unique<Block>(blockId, c, false);
}
