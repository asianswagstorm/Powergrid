#ifndef PART5_SUMMARYCARD_H
#define PART5_SUMMARYCARD_H
#include <iostream>
//#include "Player.h"
class SummaryCard {

public:
    SummaryCard();
    ~SummaryCard();
    void SummaryCardInfo();
//    void setTurnCounter(int turnCounter);
//    int getTurnCounter();
//    void turnOrder();
//    void buyPowerPlant();
//    void buyRawMaterial();
//    void building();
//    void bureaucracy();

private:
    int turnCounter;
    //std::vector<Player*> vector_player;
    int nbOfPlayer = 0;
};
#endif //PART5_SUMMARYCARD_H
