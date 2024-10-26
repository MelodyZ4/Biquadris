#include "level.h"

Level::~Level() {}

Level::Level(int level) { this->level = level; }

void Level::setisRandom(bool rand) { isRandom = rand; }

bool Level::getRandom() { return isRandom; }

int Level::getLevel() const { return this->level; }

void Level::turnOnRandom() { isRandom = true; }

void Level::turnOffRandom(const std::vector<char> &sequence) {
  for (auto ch : sequence) noRandomSequence.push_back(ch);
  noRandomCount = 0;
  isRandom = false;
}

std::unique_ptr<Block> Level::createBlock(char c, int blockId, bool heavy) {
  return std::make_unique<Block>(blockId, c, heavy);
}
