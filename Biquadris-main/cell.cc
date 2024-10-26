#include "cell.h"

Cell::Cell(int row, int col, char c, int blockId): row{row}, col{col}, c{c}, blockId{blockId} {}

char Cell::getChar() const { return c; }
int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
void Cell::setCoords(int row, int col) { this->row = row; this->col = col; }
void Cell::setChar(char c) { this->c = c;}

int Cell::getBlockId() const { return blockId; }

