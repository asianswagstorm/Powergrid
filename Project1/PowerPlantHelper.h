#pragma once
#include "PowerPlant.h"
#include <vector>
#include <algorithm>

using namespace std;

class PowerPlantHelper {


public:
	PowerPlantHelper();
	~PowerPlantHelper();

	void printPPMarket();

	int findPPActual(int typeNum);


	bool isPPActual(int typeNum);
	vector<PowerPlant> * getPPV();

	void setPPV(vector<PowerPlant> * ppv);

	string getPlantType(int i);

	int getPlantResources(int i);
	
	PowerPlant* removePowerPlant(int playerBid);

	bool isStep3 = false;
private:
	vector<PowerPlant> * ppv;
	vector<PowerPlant> *powerplantCardsShowned;
	vector<PowerPlant> *powerplantActualMarket;
};