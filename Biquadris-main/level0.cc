#include "level0.h"

#include <fstream>
using namespace std;

Level0::Level0(const std::string &s) : Level{0} {
  ifstream f{s};
  char c;
  while (f >> c) sequence.emplace_back(c);
}

unique_ptr<Block> Level0::createBlock(int blockId) {
  count += 1;
  return make_unique<Block>(blockId, sequence[(count - 1) % sequence.size()],
                            0);
}
