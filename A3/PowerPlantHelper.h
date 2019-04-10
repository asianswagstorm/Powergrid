#pragma once
#include "Powerplant.h"
#include "Player.h"
#include <vector>
#include <algorithm>

using namespace std;

class PowerPlantHelper {


public:
	PowerPlantHelper();
	~PowerPlantHelper();

	void printPPMarket();

	int findPPActual(int typeNum);

	int findPowerPlant(int bid);

	bool isPPActual(int typeNum);
	vector<PowerPlant> * getPPV();

	void setPPV(vector<PowerPlant> * ppv);

	string getPlantType(int i);

	vector<PowerPlant> *getPPVActualMarket();
	int getPlantResources(int i);
	
	PowerPlant removePowerPlant(int playerBid, Player * p);

	bool isStep3 = false;
private:
	vector<PowerPlant> * ppv;
	vector<PowerPlant> * ppvClone;
	vector<PowerPlant> * powerplantCardsShowned;
	vector<PowerPlant> * powerplantActualMarket;
};