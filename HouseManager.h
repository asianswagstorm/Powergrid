#ifndef PART3_HOUSEMANAGER_H
#define PART3_HOUSEMANAGER_H
#include <iostream>
#include <vector>
#include "House.h"
using namespace std;

class HouseManager{
public:
    HouseManager();
    ~HouseManager();
    void setHouseCount(int houseCount);
    void addHouses(House house);
    vector<int>* getHouseIndices();
    int getHouseCount();

    vector <House> getHouseVector();

    bool isHouseCountMax();

    int getArea(int index);

private:

    const int MAX_HOUSE_COUNT = 22;
    int houseCount;
    vector<House> * houseVector;
};

#endif //PART3_HOUSEMANAGER_H
