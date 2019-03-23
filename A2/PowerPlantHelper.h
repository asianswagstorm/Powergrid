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

	int findPP(int typeNum);


	vector<PowerPlant> * getPPV();

	void setPPV(vector<PowerPlant> * ppv);

	string getPlantType(int index);

	int getPlantReq(int index);


private:
	vector<PowerPlant> * ppv;
	vector<PowerPlant> *powerplantCardsShowned;
};