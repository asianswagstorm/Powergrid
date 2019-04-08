#pragma once
#include <iostream>
#include <vector>
#include "House.h"
using namespace std;
class HouseHelper {
public:
	HouseHelper();
	~HouseHelper();
	void setHouse(int house);
	void addHouse(House house);
	std::vector<int>* getHouseLocation() const; 
	int getHouse() const; //get number of houses
	
	std::vector <House> getHouseVector();

private:

	int houseCounter;
	std::vector<House> * houseVector;
};
