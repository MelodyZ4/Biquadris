#include "model.h"

#include "blind.h"
#include "boardbase.h"
#include "force.h"
#include "heavy.h"

using namespace std;

BiquadrisModel::BiquadrisModel()
    : playerOne{make_unique<BoardBase>()},
      playerTwo{make_unique<BoardBase>()},
      currPlayer{nullptr} {
  currPlayer = playerOne.get();
}

BiquadrisModel::~BiquadrisModel() {}

void BiquadrisModel::init() {
  playerOne->init();
  playerTwo->init();
}

Board *BiquadrisModel::getPlayerOne() const { return playerOne.get(); }

Board *BiquadrisModel::getPlayerTwo() const { return playerTwo.get(); }

Board *BiquadrisModel::getCurrPlayer() const { return currPlayer; }

int BiquadrisModel::switchPlayer() {
  // int rowsCleared=currPlayer->update();
  if (currPlayer == playerOne.get() || playerOne.get()->ifLost())
    currPlayer = playerTwo.get();
  else if (currPlayer == playerTwo.get() || playerTwo.get()->ifLost())
    currPlayer = playerOne.get();
  // return rowsCleared;
  return 0;
}

// Do we terminate the game only when both players lost the game?
bool BiquadrisModel::getstated() {
  return (
      playerOne->ifLost() and
      playerTwo
          ->ifLost());  // return (playerOne->ifLost() or playerTwo->ifLost());
}

void BiquadrisModel::applySpecialAction(std::string action, bool isPlayerOne,
                                        char c) {
  std::unique_ptr<Board> board =
      (isPlayerOne ? std::move(playerOne) : std::move(playerTwo));
  if (action == "heavy") {
    board = std::make_unique<Heavy>(std::move(board));
  } else if (action == "blind") {
    board = std::make_unique<Blind>(std::move(board));
  } else if (action == "force") {
    board = std::make_unique<Force>(std::move(board));
    board->forceCurrBlock(c);
  }

  // assign back to the currPlayer (playerOne or playerTwo)
  if (isPlayerOne) {
    playerOne = std::move(board);
  } else {
    playerTwo = std::move(board);
  }
}

void BiquadrisModel::removeSpecialAction(bool isPlayerOne) {
  if (isPlayerOne) {
    playerOne = playerOne->getBaseBoard();
    currPlayer = playerOne.get();
  } else {
    playerTwo = playerTwo->getBaseBoard();
    currPlayer = playerTwo.get();
  }
}
