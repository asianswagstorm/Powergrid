#include "RandomStrategy.h"
#include "IOFile.h"
#include "PowerPlantHelper.h"

RandomStrategy::RandomStrategy() {}
RandomStrategy::RandomStrategy(Player *p) {
	execute(p);
}
RandomStrategy::~RandomStrategy() {}

//always perform a random action
int RandomStrategy::execute(Player*) {
	
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
	int randomIndex = rand() % powerplantActualMarket->size();
	int random = (*powerplantActualMarket)[randomIndex].getTypeNum();
	
	return random; }

