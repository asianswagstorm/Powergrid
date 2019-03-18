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
    int getHouse();
    void printPowerPlantSummary();
	static void pool();

private:
    int minPlantCost;
    string type;
    int typeNum;
    int house;
};

#endif //POWERPLANT_H