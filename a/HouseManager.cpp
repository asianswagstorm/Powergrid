#include <iostream>
#include <string>
#include "HouseManager.h"

using namespace std;

//Default constructor
HouseManager::HouseManager(){
    houseCount = 0;
    houseVector = new vector<House>();

    houseVector->clear();
}

//Destructor
HouseManager::~HouseManager(){

}

//Setter to take into account the number of houses/cities claimed bought
void HouseManager::setHouseCount(int houseCount){
    this->houseCount = houseCount;
}

//Getter
int HouseManager::getHouseCount(){
    return houseCount;
}

//returns the house vector
vector<House> HouseManager::getHouseVector()
{
    return *houseVector;
}

//Check if the maximum number of houses per player is reached
bool HouseManager::isHouseCountMax()
{
    return houseCount == MAX_HOUSE_COUNT;
}

int HouseManager::getArea(int index)
{
    if (index < 7) {
        return 0;
    }
    else if (index < 14) {
        return 1;
    }
    else if (index < 21) {
        return 2;
    }
    else if (index < 28) {
        return 3;
    }
    else if (index < 35) {
        return 4;
    }
    return 5;
}

//Adding the number of bought houses/cities to the collection
void HouseManager::addHouses(House house)
{
    houseVector->push_back(house);
    houseCount++;
}

//returns only the indices of the player
vector<int> * HouseManager::getHouseIndices() {
    vector<int> * houses = new vector<int>();

    for (House h : *houseVector) {
        houses->push_back(h.getIndex());
    }
    return houses;
}
