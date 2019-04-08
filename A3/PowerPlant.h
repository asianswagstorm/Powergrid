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
    PowerPlant(int, string, int, int, bool, string);
    void setMinPlantCost(int minPlantCost);
    void setTypeNum(int typeNum);
    void setType(string type);
    void setHouse(int house);
    int getMinPlantCost();
	string getType();
    int getTypeNum();
	int getStorage();
    int getHouse();
	string getOwner();
	bool getInDeck();
	void setInDeck(bool inDeck);
	void setOwner(string ownedBy);

    void printPowerPlantSummary();

private:

    int minPlantCost;
    string type;
    int typeNum;
    int house;
	int storage = 2 * minPlantCost;
	bool inDeck;
	string ownedBy;
};

#endif //POWERPLANT_H