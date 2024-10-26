#include "block.h"

#include <iostream>
#include <memory>
#include <vector>

#include "cell.h"

using namespace std;

Block::Block(int blockId, char type, bool heavy) : id{blockId} {
  if (type == '*') {
    // Cell c1(0, 0, '*', blockId);
    this->v.emplace_back(0, 0, '*', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 14;
    left = 5;
    bottom = 14;
    right = 5;
  }

  else if (type == 'Z') {
    // Cell c1(1, 0, 'Z', blockId);
    // Cell c2(1, 1, 'Z', blockId);
    // Cell c3(0, 1, 'Z', blockId);
    // Cell c4(0, 2, 'Z', blockId);
    this->v.emplace_back(1, 0, 'Z', blockId);
    this->v.emplace_back(1, 1, 'Z', blockId);
    this->v.emplace_back(0, 1, 'Z', blockId);
    this->v.emplace_back(0, 2, 'Z', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (type == 'S') {
    // Cell c1(0, 0, 'S', blockId);
    // Cell c2(0, 1, 'S', blockId);
    // Cell c3(1, 1, 'S', blockId);
    // Cell c4(1, 2, 'S', blockId);

    this->v.emplace_back(0, 0, 'S', blockId);
    this->v.emplace_back(0, 1, 'S', blockId);
    this->v.emplace_back(1, 1, 'S', blockId);
    this->v.emplace_back(1, 2, 'S', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (type == 'O') {
    // Cell c1(0, 0, 'O', blockId);
    // Cell c2(0, 1, 'O', blockId);
    // Cell c3(1, 0, 'O', blockId);
    // Cell c4(1, 1, 'O', blockId);

    this->v.emplace_back(0, 0, 'O', blockId);
    this->v.emplace_back(0, 1, 'O', blockId);
    this->v.emplace_back(1, 0, 'O', blockId);
    this->v.emplace_back(1, 1, 'O', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 1;

  } else if (type == 'T') {
    Cell c1(1, 0, 'T', blockId);
    Cell c2(1, 1, 'T', blockId);
    Cell c3(1, 2, 'T', blockId);
    Cell c4(0, 1, 'T', blockId);

    this->v.emplace_back(c1);
    this->v.emplace_back(c2);
    this->v.emplace_back(c3);
    this->v.emplace_back(c4);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (type == 'L') {
    // Cell c1(0, 0, 'L', blockId);
    // Cell c2(0, 1, 'L', blockId);
    // Cell c3(0, 2, 'L', blockId);
    // Cell c4(1, 2, 'L', blockId);

    this->v.emplace_back(0, 0, 'L', blockId);
    this->v.emplace_back(0, 1, 'L', blockId);
    this->v.emplace_back(0, 2, 'L', blockId);
    this->v.emplace_back(1, 2, 'L', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else if (type == 'J') {
    // Cell c1(0, 0, 'J', blockId);
    // Cell c2(0, 1, 'J', blockId);
    // Cell c3(0, 2, 'J', blockId);
    // Cell c4(1, 0, 'J', blockId);

    this->v.emplace_back(0, 0, 'J', blockId);
    this->v.emplace_back(0, 1, 'J', blockId);
    this->v.emplace_back(0, 2, 'J', blockId);
    this->v.emplace_back(1, 0, 'J', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 15;
    left = 0;
    bottom = 14;
    right = 2;

  } else {  // (type == 'I')

    Cell c1(0, 0, 'I', blockId);
    Cell c2(0, 1, 'I', blockId);
    Cell c3(0, 2, 'I', blockId);
    Cell c4(0, 3, 'I', blockId);

    this->v.emplace_back(0, 0, 'I', blockId);
    this->v.emplace_back(0, 1, 'I', blockId);
    this->v.emplace_back(0, 2, 'I', blockId);
    this->v.emplace_back(0, 3, 'I', blockId);
    this->c = type;
    this->heavy = heavy;
    top = 14;
    left = 0;
    bottom = 14;
    right = 3;
  }
}

Block::~Block() {}

vector<Cell> Block::getposition() { return v; }

int Block::getTop() { return this->top; }

int Block::getLeft() { return this->left; }

int Block::getBottom() { return this->bottom; }

int Block::getRight() { return this->right; }

int Block::getBlockId() const { return id; }

void Block::setHeavy(bool heavy) { this->heavy = heavy; }

void Block::rotatecw(vector<vector<Cell>> &grid) {
  int t1 = top;
  int t2 = left;
  int t3 = bottom;
  int t4 = right;
  int diffrow = t1 - t3;
  int diffcol = t4 - t2;

  // check for collisions
  for (Cell cell : v) {
    int r1 = cell.getRow();
    int c1 = cell.getCol();
    int r2 = -1 * c1 + diffcol + bottom;
    int c2 = r1 + left;

    if (r2 < 0 || c2 > 10 || c2 < 0 || grid[17 - r2][c2].getChar() != '_') {
      return;  // fail -> we return
    }
  }

  // no collisions -> safely change coordinates
  for (Cell &cell : v) {
    int r1 = cell.getRow();
    int c1 = cell.getCol();
    int r2 = -1 * c1 + diffcol;
    int c2 = r1;
    cell.setCoords(r2, c2);
    // cout<<r2<<' '<<c2<<'\n';
  }
  top = t3 + diffcol;
  right = t2 + diffrow;
  if (heavy) {
    moveDown(grid);
  }
  return;
}

void Block::rotateccw(vector<vector<Cell>> &grid) {
  int t1 = top;
  int t2 = left;
  int t3 = bottom;
  int t4 = right;
  int diffrow = t1 - t3;
  int diffcol = t4 - t2;

  // check for collisions
  for (Cell cell : v) {
    int r1 = cell.getRow();
    int c1 = cell.getCol();
    int r2 = c1 + bottom;
    int c2 = -1 * r1 + diffrow + left;

    if (r2 < 0 || c2 > 10 || c2 < 0 || grid[17 - r2][c2].getChar() != '_') {
      return;  // fail -> we return
    }
  }

  // no collisions -> safely change coordinates
  for (Cell &cell : v) {
    int r1 = cell.getRow();
    int c1 = cell.getCol();
    int r2 = c1;
    int c2 = -1 * r1 + diffrow;
    cell.setCoords(r2, c2);
  }
  top = t3 + diffcol;
  right = t2 + diffrow;
  if (heavy) {
    moveDown(grid);
  }
  return;
}

// helper function
bool Block::mover(int r, int c, const vector<Cell> &v,
                  vector<vector<Cell>> &grid) {
  // check for collisions
  for (Cell cell : v) {
    int r1 = cell.getRow();
    int c1 = cell.getCol();
    int r2 = r1 + r + bottom;
    int c2 = c1 + c + left;

    if (r2 < 0 || c2 > 10 || c2 < 0 || (grid[17 - r2][c2].getChar() != '_')) {
      return false;  // fail -> we return
    }
  }

  // no collisions -> safely change coordinates
  return true;
}

void Block::moveLeft(vector<vector<Cell>> &grid) {
  if (mover(0, -1, v, grid)) {
    left -= 1;
    right -= 1;
  }

  if (heavy) {
    moveDown(grid);
  }
}
void Block::moveRight(vector<vector<Cell>> &grid) {
  if (mover(0, 1, v, grid)) {
    left += 1;
    right += 1;
  }
  if (heavy) {
    moveDown(grid);
  }
}
void Block::moveDown(vector<vector<Cell>> &grid) {
  if (mover(-1, 0, v, grid)) {
    top -= 1;
    bottom -= 1;
  }

  if (heavy && mover(-1, 0, v, grid)) {
    top -= 1;
    bottom -= 1;
  }
}

void Block::drop(vector<vector<Cell>> &grid) {
  // idea: move down until failure
  while (true) {
    int b1 = this->bottom;
    this->moveDown(grid);
    int b2 = this->bottom;
    if (b1 == b2) {
      break;
    }
  }
}

bool Block::heavyDown(vector<vector<Cell>> &grid) {
  // idea: move down until failure
  for (int i = 0; i < 2; ++i) {
    int b1 = this->bottom;
    this->moveDown(grid);
    int b2 = this->bottom;
    if (b1 == b2) {
      return true;
    }
  }
  return false;
}

char Block::getChar() { return this->c; }
