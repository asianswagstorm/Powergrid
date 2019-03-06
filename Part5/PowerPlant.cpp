#include <iostream>
#include <string>
#include "PowerPlant.h"

using namespace std;

//Default constructor
PowerPlant::PowerPlant(){
    minPlantCost = 1;
    type = "null";
    typeNum = 1;
    house = 1;

}

//Constructor initializes power plants 
PowerPlant::PowerPlant(int minPlantCost, string type, int typeNum, int house){
    this->minPlantCost = minPlantCost;
    this->type = type; 
    this->typeNum = typeNum;
    this->house = house;

}

//Destructor
PowerPlant::~PowerPlant(){

}

//Mutator function for setting the minimal cost of a power plant
void PowerPlant::setMinPlantCost(int minPlantCost){
    this->minPlantCost = minPlantCost;
}

//Mutator function for setting the type of resources needed to fuel the power plant
void PowerPlant::setType(string type) {
    this->type = type;
}

void PowerPlant::setTypeNum(int typeNum) {
    this->typeNum = typeNum;
}

//Mutator function for setting the number of house/city the power plant can power
void PowerPlant::setHouse(int house){
    this->house = house;
}

//Accessor function to get the minimum bidding cost of the power plant
int PowerPlant::getMinPlantCost(){
    return minPlantCost;
}

//Accessor function to get the type of resources or raw material it needs to power
string PowerPlant::getType(){
    return type;
}


int PowerPlant::getTypeNum() {
    return typeNum;
}

//Accessor function that gets the number of houses the power plant can power
int PowerPlant::getHouse(){
    return house;
}

//Function that prints out the summary of each power plants
 void PowerPlant::printPowerPlantSummary(){
    cout << "*****************************************************************" << endl;
    cout << "This is the power plant and it's stats: " << endl;
    cout << "This is the minimum cost: " << minPlantCost << endl;
    cout << "This is the resource needed: " << type << endl;
    cout << "This is the number of resource needed: " << type << endl;
    cout << "This is the amount of house it can power: " << house << endl;
    cout << "*****************************************************************" << endl;
}