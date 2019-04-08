#include <iostream>
#include <algorithm>
#include <string>

#include "SummaryCard.h"
#include "PowerPlant.h"
//#include "Resource.h"
#include "PowerPlant.h"

using namespace std;

//Default constructor
SummaryCard::SummaryCard(){
    turnCounter = 0; //keep track of who is going first
    nbOfPlayer = 0; //how many people are playing in this game. for now we will have 2 only.
}

//Constructor
//SummaryCard::SummaryCard(std::vector<Player*> vector_player){
//    turnCounter = 1;
//    this->vector_player = vector_player;
//    nbOfPlayer = vector_player.size();
//}

//Destructor
SummaryCard::~SummaryCard(){

}

void SummaryCard::SummaryCardInfo() {
    cout << "SUMARRY CAR: TURN \n" << "=================== \n"
         << "1.DETERMINE TURN ORDER \n"
         << "2.BUY POWER PLANT \n" << "  The first player begins \n" << "  Per round, each may buy only one power plant. \n"
         << "3.BUY RAW MATERIALS \n" << "  The last player beings.\n" << "  Maximum double input per power plant.\n"
         << "4.BUILDING \n" << "  The last player begins.\n"
         << "5.BUREAUCRACY \n" << "  -Get money.\n" << "  -In phase 1 and 2: Place highest power plant under de stack.\n"
         << "  -In phase 3: Remove the lower power plant from the game. \n"
         << "  -Restock raw materials" << endl;
}