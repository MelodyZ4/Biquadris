#ifndef __CELL_H__
#define __CELL_H__

class Cell {
  int row, col;
  char c;
  int blockId; // default -1 no block 'attached'

 public:
  Cell(int row, int col, char c, int blockId = -1);
  char getChar() const;  // Returns the value of r.
  int getRow() const; // Returns the value of row.
  int getCol() const; // Returns the value of col.
  void setCoords(int r, int c);  // Changes my row and column number.
  void setChar(char c);

  int getBlockId() const;
};
#endif
