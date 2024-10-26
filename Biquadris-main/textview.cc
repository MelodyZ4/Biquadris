#include "textview.h"
#include <iomanip>
using namespace std;

TextView::~TextView(){

}

TextView::TextView(BiquadrisModel *m, BiquadrisController *c)
    : model{m}, controller{c}
{}

void TextView::printNext1(char ch) {
    if (ch == 'I') {
        cout << "           ";
    } else if (ch == 'Z') {
        cout << "ZZ         ";
    } else if (ch == 'S') {
        cout << " SS        ";
    } else if (ch == 'J') {
        cout << "J          ";
    } else if (ch == 'O') {
        cout << "OO         ";
    } else if (ch == 'T') {
        cout << "TTT        ";
    } else { // ch == 'L'
        cout << "  L        ";
    }
}

void TextView::printNext2(char ch) {
    if (ch == 'I') {
        cout << "IIII       ";
    } else if (ch == 'Z') {
        cout << " ZZ        ";
    } else if (ch == 'S') {
        cout << "SS         ";
    } else if (ch == 'J') {
        cout << "JJJ        ";
    } else if (ch == 'O') {
        cout << "OO         ";
    } else if (ch == 'T') {
        cout << " T         ";
    } else { // ch == 'L'
        cout << "LLL        ";
    }
}

void TextView::displayGame() {
    Board* p1 = model->getPlayerOne();
    Board* p2 = model->getPlayerTwo();
    vector<vector<char>>board1 = p1->getBoard();
    vector<vector<char>>board2 = p2->getBoard();
    
    cout << "Level:" << setw(5) << p1->getCurrLevel() << "          " << "Level:" << setw(5) << p2->getCurrLevel() << endl;
    cout << "Score:" << setw(5) << p1->getCurrScore() << "          " << "Score:" << setw(5) << p2->getCurrScore() << endl;

    cout << "-----------          -----------" << endl;

    for (int r = 0; r < 18; ++r) {
        for (int c = 0; c < 11; ++c) cout << board1[r][c];
        cout << "          ";
        for (int c = 0; c < 11; ++c) cout << board2[r][c];
        cout << endl;
    }

    cout << "-----------          -----------" << endl;
    cout << "Next:                Next:      " << endl;

    char type1 = p1->getNextBlock()->getChar();
    char type2 = p2->getNextBlock()->getChar();
    printNext1(type1);
    cout << "          ";
    printNext1(type2);
    cout << endl;
    printNext2(type1);
    cout << "          ";
    printNext2(type2);
    cout << endl;

    cout << "================================" << endl;
}






