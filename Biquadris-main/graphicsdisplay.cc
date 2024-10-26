#include "graphicsdisplay.h"

#include <iomanip>
#include <map>
#include <unordered_map>

#include "board.h"
#include "controller.h"
#include "model.h"
using namespace std;

// const int ROWS = 18;
// const int COLUMNS = 11;

const int SQUARE_WIDTH = 25;
const int BORDER_WIDTH = 2;

const int BOARD_WIDTH = SQUARE_WIDTH * COLS;
const int BOARD_HEIGHT = SQUARE_WIDTH * ROWS;

const int PLAYER1_X = 20;
const int PLAYER2_X = 315;
const int PLAYERS_Y = 50;
const int BOARD_Y = 100;

// Black, Orange,Cyan, Blue, Yellow, Green, Purple, Red, Browns
const std::unordered_map<char, int> BLOCKS_COLOUR{
    {'I', Xwindow::Cyan},   {'J', Xwindow::Blue},   {'L', Xwindow::Yellow},
    {'O', Xwindow::Green},  {'S', Xwindow::Purple}, {'Z', Xwindow::Red},
    {'T', Xwindow::Orange}, {'*', Xwindow::Brown},  {'?', Xwindow::White},
    {'_', Xwindow::Black}};

std::map<char, std::vector<std::pair<int, int>>> BLOCKS_POS{
    {'I', {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
    {'J', {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
    {'L', {{2, 0}, {0, 1}, {1, 1}, {2, 1}}},
    {'O', {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
    {'S', {{1, 0}, {2, 0}, {0, 1}, {1, 1}}},
    {'Z', {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
    {'T', {{0, 0}, {1, 0}, {2, 0}, {1, 1}}},
    {' ', {}}};

void GraphicsView::displayNextBlock(char type, int p) {
  auto pos = BLOCKS_POS[type];
  int offset = (p == 1 ? 20 : 315);
  for (const auto &p : pos) {
    int x = 25 * p.first + offset;
    int y = 620 + 25 * p.second;
    w.fillRectangle(x, y, SQUARE_WIDTH - 2, SQUARE_WIDTH - 2,
                    BLOCKS_COLOUR.at(type));
  }
}

GraphicsView::GraphicsView(BiquadrisModel *m, BiquadrisController *c)
    : model{m}, controller{c} {
  for (size_t i = 0; i < ROWS; ++i) {
    playerOne.emplace_back();
    playerTwo.emplace_back();
    for (size_t j = 0; j < COLS; ++j) {
      playerOne[i].push_back('_');
      playerTwo[i].push_back('_');
    }
  }

  w.drawString(20, 40, "Level       :");
  w.drawString(315, 40, "Level       :");
  w.drawString(20, 60, "HiScore     :");
  w.drawString(315, 60, "HiScore     :");
  w.drawString(20, 80, "Score       :");
  w.drawString(315, 80, "Score       :");

  w.fillRectangle(PLAYER1_X, BOARD_Y, BOARD_WIDTH + BORDER_WIDTH,
                  BOARD_HEIGHT + BORDER_WIDTH, Xwindow::Black);
  w.fillRectangle(PLAYER2_X, BOARD_Y, BOARD_WIDTH + BORDER_WIDTH,
                  BOARD_HEIGHT + BORDER_WIDTH, Xwindow::Black);

  w.drawString(PLAYER1_X, 590, "Next     :");
  w.drawString(PLAYER2_X, 590, "Next     :");
}

GraphicsView::~GraphicsView() {}

std::string padding(const std::string s, int width) {
  stringstream ss;
  ss << setw(width) << s;
  return ss.str();
}

void GraphicsView::displayGame() {
  auto p1 = model->getPlayerOne();
  auto p2 = model->getPlayerTwo();
  auto currPlayer = model->getCurrPlayer();
  auto board1 = p1->getBoard();
  auto board2 = p2->getBoard();

  w.fillRectangle(100, 20, 100, 80, Xwindow::White);
  w.fillRectangle(395, 20, 100, 80, Xwindow::White);

  std::string p1Level{padding(std::to_string(p1->getCurrLevel()), 5)};
  w.drawString(120, 40, p1Level);

  std::string p2Level{padding(std::to_string(p2->getCurrLevel()), 5)};
  w.drawString(415, 40, p2Level);

  std::string p1HiScore{padding(std::to_string(p1->getHiScore()), 5)};
  w.drawString(120, 60, p1HiScore);

  std::string p2HiScore{padding(std::to_string(p2->getHiScore()), 5)};
  w.drawString(415, 60, p2HiScore);

  std::string p1Score{padding(std::to_string(p1->getCurrScore()), 5)};
  w.drawString(120, 80, p1Score);

  std::string p2Score{padding(std::to_string(p2->getCurrScore()), 5)};
  w.drawString(415, 80, p2Score);

  // Print both boards
  for (size_t r = 0; r < ROWS; ++r) {
    for (size_t c = 0; c < COLS; ++c) {
      if (board1[r][c] != playerOne[r][c]) {
        int colour = BLOCKS_COLOUR.at(board1[r][c]);
        w.fillRectangle(PLAYER1_X + SQUARE_WIDTH * c + BORDER_WIDTH,
                        BOARD_Y + SQUARE_WIDTH * r + BORDER_WIDTH,
                        SQUARE_WIDTH - BORDER_WIDTH,
                        SQUARE_WIDTH - BORDER_WIDTH, colour);
      }

      if (board2[r][c] != playerTwo[r][c]) {
        int colour = BLOCKS_COLOUR.at(board2[r][c]);
        w.fillRectangle(315 + SQUARE_WIDTH * c + BORDER_WIDTH,
                        BOARD_Y + SQUARE_WIDTH * r + BORDER_WIDTH,
                        SQUARE_WIDTH - BORDER_WIDTH,
                        SQUARE_WIDTH - BORDER_WIDTH, colour);
      }
    }
  }

  w.fillRectangle(315, 620, 100, 50, Xwindow::White);
  w.fillRectangle(20, 620, 100, 50, Xwindow::White);

  char currPlayerNext = currPlayer->getNextBlock()->getChar();
  displayNextBlock(currPlayerNext, currPlayer == p1 ? 1 : 2);

  playerOne = std::move(board1);
  playerTwo = std::move(board2);
}
