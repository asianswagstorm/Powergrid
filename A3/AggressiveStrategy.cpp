#include "AggressiveStrategy.h"
#include "IOFile.h"
#include "PowerPlantHelper.h"
/*
An aggressive player, where anytime a good power plant becomes available, this player continue to bid
especially if it's early in the game (e.g. a five city double coal power plant early is worth a lot,. Ideally
this player should strive to purchase a third power plant that will not need to be replaced).

always pick highest powerplant num
*/



AggressiveStrategy::AggressiveStrategy() {}


AggressiveStrategy::AggressiveStrategy(Player *p) {
	execute(p);
}

AggressiveStrategy::~AggressiveStrategy() {}


int AggressiveStrategy::execute(Player *p) {
	
	vector<Player*> players = IOFile::loadPlayer();
	
	vector<PowerPlant> * powerplants = IOFile::loadPowerplants(players);
	vector<PowerPlant> * powerplantCardsShowned = new vector<PowerPlant>();
	vector<PowerPlant> * powerplantActualMarket = new vector<PowerPlant>();
	PowerPlantHelper * powerplanthelper = new PowerPlantHelper();
	powerplanthelper->PowerPlantHelper::setPPV(IOFile::loadPowerplants(players));
	
	for (int i = 0; i < 4; i++) {
		powerplantCardsShowned->push_back((*powerplants)[i]);
		if (i < 4)
			powerplantActualMarket->push_back((*powerplantCardsShowned)[i]);
	}
	
	int max = 0;
	for (unsigned int j = 0; j < powerplantActualMarket->size(); j++) {
		if ((*powerplantActualMarket)[j].getTypeNum() > max) {
			max = (*powerplantActualMarket)[j].getTypeNum();
		}
	}
	//std::cout << "Max is: " << max <<std::endl;
	
	return max;
}
