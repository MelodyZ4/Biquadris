#ifndef __BIQUADRIS_MODEL_H__
#define __BIQUADRIS_MODEL_H__
#include "subject.h"
#include "level.h"
#include "boardbase.h"
#include <memory>
#include <string>

class BiquadrisModel : public Subject {
    std::unique_ptr<Board> playerOne;
    std::unique_ptr<Board> playerTwo;
    Board *currPlayer;

   public:
    BiquadrisModel();
    ~BiquadrisModel();
    void init();
    Board *getCurrPlayer() const;
    Board *getPlayerOne() const;
    Board *getPlayerTwo() const;
    int switchPlayer();
    bool getstated();
    void applySpecialAction(std::string action, bool isPlayerOne, char block = 'z'); 
    void removeSpecialAction(bool isPlayerOne); 
};

#endif

