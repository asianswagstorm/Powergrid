#include "PowerPlantHelper.h"
#include "PowerPlant.h"
#include <vector>
#include <algorithm> 
#include <ctime> 
#include <iostream>

using namespace std;

PowerPlantHelper::PowerPlantHelper()
{
	PowerPlant coal4(4, "Coal", 2, 1);
	PowerPlant coal8(8, "Coal", 3, 2);
	PowerPlant coal10(10, "Coal", 2, 2);
	PowerPlant coal15(15, "Coal", 2, 3);
	PowerPlant coal20(20, "Coal", 3, 5);
	PowerPlant coal25(25, "Coal", 2, 5);
	PowerPlant coal31(31, "Coal", 3, 6);
	PowerPlant coal36(36, "Coal", 3, 7);
	PowerPlant coal42(42, "Coal", 2, 6);

	PowerPlant oil3(3, "Oil", 2, 1);
	PowerPlant oil7(7, "Oil", 3, 2);
	PowerPlant oil9(9, "Oil", 1, 1);
	PowerPlant oil16(16, "Oil", 2, 3);
	PowerPlant oil26(26, "Oil", 2, 5);
	PowerPlant oil32(32, "Oil", 3, 6);
	PowerPlant oil35(35, "Oil", 1, 5);
	PowerPlant oil40(40, "Oil", 2, 6);

	PowerPlant hybrid5(5, "Hybrid", 2, 1);
	PowerPlant hybrid12(12, "Hybrid", 2, 2);
	PowerPlant hybrid21(21, "Hybrid", 2, 4);
	PowerPlant hybrid29(29, "Hybrid", 1, 4);
	PowerPlant hybrid46(46, "Hybrid", 3, 7);

	PowerPlant garbage6(6, "Garbage", 1, 1);
	PowerPlant garbage14(14, "Garbage", 2, 2);
	PowerPlant garbage19(19, "Garbage", 2, 3);
	PowerPlant garbage24(24, "Garbage", 2, 4);
	PowerPlant garbage30(30, "Garbage", 3, 6);
	PowerPlant garbage38(38, "Garbage", 3, 7);

	PowerPlant uranium11(11, "Uranium", 1, 1);
	PowerPlant uranium17(17, "Uranium", 1, 2);
	PowerPlant uranium23(23, "Uranium", 1, 3);
	PowerPlant uranium28(28, "Uranium", 1, 4);
	PowerPlant uranium34(34, "Uranium", 1, 5);
	PowerPlant uranium39(39, "Uranium", 1, 6);

	PowerPlant eco13(13, "Eco", 0, 1);
	PowerPlant eco18(18, "Eco", 0, 2);
	PowerPlant eco22(22, "Eco", 0, 2);
	PowerPlant eco27(27, "Eco", 0, 3);
	PowerPlant eco33(33, "Eco", 0, 4);
	PowerPlant eco37(37, "Eco", 0, 4);
	PowerPlant eco44(44, "Eco", 0, 5);
	PowerPlant eco50(50, "Eco", 0, 6);

	PowerPlant step3(-1, "Step 3", -1, -1);

	/*Take the power plant cards numbered 03 to 10 and place them near the board in two horizontal rows.These power plants are an array of 2 x 4 cards(the power plant
		market).In the upper row, place power plants numbered 03 to 06 in ascending order, left to right, beginning with the least expensive; this is the actual market.In the
		lower row, place power plants numbered 07 to 10 in ascending order, left to right; this is the future market.

		When players add new power plants to the power plant
		market, players rearrange all power plants in the power plant market in ascending order with the 4 cheapest plants in the actual market.
	*/
	//PowerPlant Start
   // this is the actual market
	ppv = new vector<PowerPlant>();

	ppv->push_back(oil3);
	
	ppv->push_back(coal4);
	
	ppv->push_back(hybrid5);
	
	ppv->push_back(garbage6);
	
	//future market
	ppv->push_back(oil7);
	
	ppv->push_back(coal8);

	ppv->push_back(oil9);
	
	ppv->push_back(coal10);
	
	//PowerPlantHelper::printPPMarket(); //Temporary
	ppv->push_back(eco13); //facedown
	//PowerPlant deck in order
	ppv->push_back(uranium11);
	ppv->push_back(hybrid12);
	ppv->push_back(garbage14);
	ppv->push_back(coal15);
	ppv->push_back(oil16);
	ppv->push_back(uranium17);
	ppv->push_back(eco18);
	ppv->push_back(garbage19);
	ppv->push_back(coal20);
	ppv->push_back(hybrid21);
	ppv->push_back(eco22);
	ppv->push_back(uranium23);
	ppv->push_back(garbage24);
	ppv->push_back(coal25);
	ppv->push_back(oil26);
	ppv->push_back(eco27);
	ppv->push_back(uranium28);
	ppv->push_back(hybrid29);
	ppv->push_back(garbage30);
	ppv->push_back(coal31);
	ppv->push_back(oil32);
	ppv->push_back(eco33);
	ppv->push_back(uranium34);
	ppv->push_back(oil35);
	ppv->push_back(coal36);
	ppv->push_back(eco37);
	ppv->push_back(garbage38);
	ppv->push_back(uranium39);
	ppv->push_back(oil40);
	ppv->push_back(coal42);
	ppv->push_back(eco44);
	ppv->push_back(hybrid46);
	ppv->push_back(eco50);

	/*
The step 3 cards seperates the deck with the Bureaucracy cards.

The Step 3 Card is placed a the bottom of the Draw Deck at the beginning of the game.
Each turn, during Phase 5.Bureaucracy, the highest power plant is placed UNDER the Step 3 Card.
When the Step 3 Card is drawn, there is a stack of power plants UNDER it -- those highest plants that have been removed during Bureaucracy.
It is this stack of highest power plants that is then shuffled.
*/
	ppv->push_back(step3); //Step 3 card at the end	

	//Used to make random_shuffle random
   //See:https://stackoverflow.com/questions/13459953/random-shuffle-not-really-random
	std::srand((unsigned int)std::time(0));
	//Randomly shuffle the cards
	//from index 9 (PowerPlant 13) to end-1 (excluding step 3)
	random_shuffle(ppv->begin() + 9, ppv->end() - 1);
	std::cout << std::endl << "==================================================" << std::endl;
	std::cout << "===========Supply Deck shuffled================" << std::endl << std::endl;;
}


//destructor
PowerPlantHelper::~PowerPlantHelper() {}

void PowerPlantHelper::printPPMarket() {
	powerplantCardsShowned = new vector<PowerPlant>();

	std::cout << std::endl <<"---------------  Actual Market  ------------" << std::endl;

	for (int i = 0; i < 8; i++) { //ppv->size()
		powerplantCardsShowned->push_back((*ppv)[i]);

		if (i==4)
			std::cout << std::endl << "---------------  Future Market  ------------" << std::endl;

		(*powerplantCardsShowned)[i].printPowerPlantSummary();
		//(*ppv)[i].printPowerPlantSummary();
	}
}


int PowerPlantHelper::findPPActual(int typeNum) {

	if (ppv->size() <= 4) { // check type number in actual market.
		for (int i = 0; i < 4; i++) {
			if ((*ppv)[i].getTypeNum() == typeNum) {
				return i;
			}
		}
		return -1;
	}

	else return -1;

}

bool PowerPlantHelper::isPPActual(int typeNum) {

	if (findPPActual(typeNum) == -1) {
		return false;
	}
	return true;
}


std::vector<PowerPlant> * PowerPlantHelper::getPPV() {

	return this->ppv;
}

void PowerPlantHelper::setPPV(std::vector<PowerPlant> * ppv) {

	this->ppv = ppv;
}

string PowerPlantHelper::getPlantType(int i) {

	return (*ppv)[i].getType();
}

int PowerPlantHelper::getPlantResources(int i) {

	return (*ppv)[i].getMinPlantCost();
}
