#include "decorator.h"

#include <iostream>

#include "boardbase.h"

Decorator::Decorator(std::unique_ptr<Board> component)
    : component{std::move(component)} {}

Decorator::~Decorator() {}

std::vector<std::vector<char>> Decorator::getBoard() {
  return component->getBoard();
}
int Decorator::getCurrLevel() const { return component->getCurrLevel(); }

int Decorator::getHiScore() const { return component->getHiScore(); }

int Decorator::getCurrScore() const { return component->getCurrScore(); }

bool Decorator::blockPlaceable(char block) {
  return component->blockPlaceable(block);
}

bool Decorator::ifLost() const { return component->ifLost(); }

Block *Decorator::getCurrBlock() { return component->getCurrBlock(); }

Block *Decorator::getNextBlock() { return component->getNextBlock(); }

void Decorator::setCurrBlock(std::unique_ptr<Block> b) {
  component->setCurrBlock(std::move(b));
}

void Decorator::setNextBlock(std::unique_ptr<Block> b) {
  component->setNextBlock(std::move(b));
}

bool Decorator::moveBlock(std::string s) { return component->moveBlock(s); }

Level *Decorator::getLevel() { return component->getLevel(); }

Cell &Decorator::getCell(int x, int y) { return component->getCell(x, y); }

void Decorator::setCurrentLevel(int n) { return component->setCurrentLevel(n); }

void Decorator::setSourceFile(const std::string &filename) {
  component->setSourceFile(filename);
}

void Decorator::init() { return component->init(); }

void Decorator::reset() { return component->reset(); }

int Decorator::update() { return component->update(); }

void Decorator::forceCurrBlock(char c) { return component->forceCurrBlock(c); }

std::unique_ptr<Board> Decorator::getBaseBoard() {
  auto temp = dynamic_cast<BoardBase *>(component.get());
  if (temp == nullptr) return component->getBaseBoard();
  return std::move(component);
}

void Decorator::turnRandomOff(const std::vector<char> &sequence) {
  return component->turnRandomOff(sequence);
}
void Decorator::turnRandomOn() { return component->turnRandomOn(); }
