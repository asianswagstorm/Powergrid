#ifndef POWERPLANT_H
#define POWERPLANT_H

#include <iostream>
#include <vector>
//#include "Resource.h"
using namespace std;

class PowerPlant{
public:
    PowerPlant();
    ~PowerPlant();
    PowerPlant(int, string, int, int);
    void setMinPlantCost(int minPlantCost);
    void setTypeNum(int typeNum);
    void setType(string type);
    void setHouse(int house);
    int getMinPlantCost();
    string getType();
    int getTypeNum();
	int getStorage();
    int getHouse();
    void printPowerPlantSummary();

private:

    int minPlantCost;
    string type;
    int typeNum;
    int house;
	int storage = 2 * minPlantCost;
};

#endif //POWERPLANT_H