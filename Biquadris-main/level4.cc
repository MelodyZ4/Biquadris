#include "level4.h"

#include <fstream>
#include <random>
using namespace std;
const static char pieces[9] = {'T', 'S', 'Z', 'O', 'I', 'L', 'J', 'S', 'Z'};

Level4::Level4() : Level{4} { turnOnRandom(); }

unique_ptr<Block> Level4::createBlock(int blockId) {
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

void Level4::resetsingle() { numplaced = 0; }

int Level4::getsingle() { return numplaced; }

void Level4::placedone() { numplaced += 1; }
