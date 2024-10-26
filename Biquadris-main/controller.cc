#include "controller.h"

#include <fstream>
#include <iostream>

#include "block.h"
#include "board.h"
#include "boardbase.h"
#include "level.h"
#include "model.h"
using namespace std;

BiquadrisController::BiquadrisController(BiquadrisModel *m) : model{m} {}

BiquadrisController::~BiquadrisController() {}

void BiquadrisController::moveLeft() {
  if (model->getCurrPlayer()->moveBlock("left")) {
    return endTurn();
  }
}

void BiquadrisController::moveRight() {
  if (model->getCurrPlayer()->moveBlock("right")) {
    return endTurn();
  }
}

void BiquadrisController::moveDown() {
  if (model->getCurrPlayer()->moveBlock("down")) {
    return endTurn();
  }
}

void BiquadrisController::rotatecw() {
  model->getCurrPlayer()->moveBlock("cw");
}

void BiquadrisController::rotateccw() {
  model->getCurrPlayer()->moveBlock("ccw");
}

void BiquadrisController::drop() {
  if (model->getCurrPlayer()->moveBlock("drop")) {
    return endTurn();
  }
}

void BiquadrisController::levelUp() {
  model->getCurrPlayer()->setCurrentLevel(
      model->getCurrPlayer()->getCurrLevel() + 1);
}

void BiquadrisController::levelDown() {
  model->getCurrPlayer()->setCurrentLevel(
      model->getCurrPlayer()->getCurrLevel() - 1);
}

// Relevant only during levels 3 and 4
void BiquadrisController::turnRandomOff(const std::string &filename) {
  if (model->getCurrPlayer()->getCurrLevel() < 3) return;

  std::ifstream in{filename};
  char c;
  std::vector<char> sequence;
  while (in >> c) sequence.push_back(c);
  model->getCurrPlayer()->turnRandomOff(sequence);
}

// Relevant only during levels 3 and 4
void BiquadrisController::turnRandomOn() {
  if (model->getCurrPlayer()->getCurrLevel() < 3) return;

  model->getCurrPlayer()->turnRandomOn();
}

void BiquadrisController::restart() { model->getCurrPlayer()->reset(); }

void BiquadrisController::swapBlock(char ch) {
  // int lvl = model->getCurrPlayer()->getCurrLevel();
  // bool heaviness = false;
  // if (lvl >= 3) {
  //     heaviness = true;
  // }
  // unique_ptr<Block> b = make_unique<Block>(ch, heaviness);
  // model->getCurrPlayer()->setCurrBlock(move(b));
  return model->getCurrPlayer()->forceCurrBlock(ch);
}

void BiquadrisController::endTurn() {
  if (model->getCurrPlayer()->ifLost()) {
    model->switchPlayer();
    return;
  }
  int rowsCleared = model->getCurrPlayer()->update();
  // cout << "reached" << std::endl;
  //  if rowsCleared >= 2, prompt for special actions and apply special actions
  //  to the opponent (might want to switch player first then apply)
  bool isPlayerOne = (model->getPlayerOne() == model->getCurrPlayer());
  if (rowsCleared >= 2) {
    cout << "Enter special action from: blind, heavy, force!" << endl;
    string cmd;
    cin >> cmd;
    if (cmd == "heavy") {
      model->applySpecialAction("heavy", !isPlayerOne);
    } else if (cmd == "blind") {
      model->applySpecialAction("blind", !isPlayerOne);
    } else if (cmd == "force") {
      char c;
      cin >> c;
      model->applySpecialAction("force", !isPlayerOne, c);
    }
  }
  auto temp = dynamic_cast<BoardBase *>(model->getCurrPlayer());
  if (temp == nullptr)
    model->removeSpecialAction(
        isPlayerOne);  // not a BoardBase (i.e., specialAction was previously
                       // applied)
  model->switchPlayer();
}
