#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>

#include "cell.h"

using namespace std;

class Block {
  char c;
  vector<Cell> v;
  int top;
  int left;
  int bottom;
  int right;
  bool heavy;

  int id;

  // Piece coordinate diagram:
  //
  // Z piece:
  // topleft [][]
  //           [][] bottomright
  //
  // S piece:
  // topleft __[][]
  //         [][]__ bottomright
  //
  // O piece:
  // topleft [][]
  //         [][] bottomright
  //
  // T piece:
  // topleft [][][]
  //           []__ bottomright
  // L piece:
  // topleft __  []
  //         [][][] bottomright
  //
  // J piece:
  // topleft []
  //         [][][] bottomright
  //
  // I piece:
  // topleft [][][][] bottomright
  //

 public:
  // the offset coordinates

  Block(int blockId, char type,
        bool heavy);  // constructor must be supplied with type
  ~Block();

  int getTop();
  int getLeft();
  int getBottom();
  int getRight();

  int getBlockId() const;

  void setHeavy(bool heavy);

  void rotatecw(vector<vector<Cell>> &grid);
  void rotateccw(vector<vector<Cell>> &grid);
  void moveLeft(vector<vector<Cell>> &grid);
  void moveRight(vector<vector<Cell>> &grid);
  void moveDown(vector<vector<Cell>> &grid);
  bool heavyDown(vector<vector<Cell>> &grid);
  void drop(vector<vector<Cell>> &grid);
  bool mover(int r, int c, const vector<Cell> &v, vector<vector<Cell>> &grid);
  char getChar();
  vector<Cell> getposition();
};

#endif
