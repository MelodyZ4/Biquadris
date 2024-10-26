#include "level3.h"

#include <fstream>
#include <random>
using namespace std;
const static char pieces[9] = {'T', 'S', 'Z', 'O', 'I', 'L', 'J', 'S', 'Z'};

Level3::Level3() : Level{3} { turnOnRandom(); }

unique_ptr<Block> Level3::createBlock(int blockId) {
  if (isRandom) {
    //srand((unsigned)time(NULL));
    int random = rand() % 9;
    char c = pieces[random];
    return make_unique<Block>(blockId, c, true);
  } else {
    noRandomCount += 1;
    return make_unique<Block>(
        blockId, sequence[(noRandomCount - 1) % sequence.size()], true);
  }
}
