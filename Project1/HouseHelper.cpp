#include <iostream>
#include <string>
#include "HouseHelper.h"

//Constructor
HouseHelper::HouseHelper() {
	houseCounter = 0;
	houseVector = new std::vector<House>();

	houseVector->clear();
}

//Destructor
HouseHelper::~HouseHelper() {

}

int HouseHelper::getHouse() const {
	return this->houseCounter;
}

void HouseHelper::setHouse(int houseCounter)
{
	this->houseCounter = houseCounter;
}

std::vector<House> HouseHelper::getHouseVector()
{
	return *houseVector;
}

void HouseHelper::addHouse(House house)
{
	this->houseVector->push_back(house);
	this->houseCounter++;
}

std::vector<int>* HouseHelper::getHouseLocation() const {
	std::vector<int> * house_vector = new vector<int>();

	for (House house : *houseVector) {
		house_vector->push_back(house.getIndex());
	}
	return house_vector;
}
