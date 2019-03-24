#pragma once
#include "Powerplant.h"
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


private:
	vector<PowerPlant> * ppv;
	vector<PowerPlant> *powerplantCardsShowned;
};