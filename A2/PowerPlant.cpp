#include <iostream>
#include <string>
#include "PowerPlant.h"
#include <ctime> // std::time()
#include <algorithm> // std::random_shuffle
using namespace std;

//Default constructor
PowerPlant::PowerPlant(){
    minPlantCost = 1;
    type = "null";
    typeNum = 1;
    house = 1;

}

//Constructor initializes power plants 
PowerPlant::PowerPlant(int typeNum, string type, int minPlantCost, int house){
    this->minPlantCost = minPlantCost;
    this->type = type; 
    this->typeNum = typeNum;
    this->house = house;
	this->storage = 2 * minPlantCost;
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

int PowerPlant::getStorage() { //should be number of resources a powerplant can hold. For now do not implement
	return storage;
}

//Accessor function that gets the number of houses the power plant can power
int PowerPlant::getHouse(){
    return house;
}

//Function that prints out the summary of each power plants
 void PowerPlant::printPowerPlantSummary(){
    cout << ""<< endl;
	if (type == "Step 3") {
		cout << "This is a Step 3 Card " << endl;
	}
	else {
		cout << "CardNumber: " << typeNum << endl;
		
		if (type == "Hybrid") {
			cout << endl << "*A Hybrid type means: either Coal or Oil or Both" << endl;
		}

		if (type == "Eco") {
			cout << endl << "*An Eco type is a freebie, doesn't require any resources" << endl;
		}

		if(house == 1)
		cout << "This PowerPlant requires " << minPlantCost << " " << type << " to power " << house << " City" << endl;
		
		else
		cout << "This PowerPlant requires " << minPlantCost << " " << type << " to power " << house << " Cities" << endl;

	}
}

 //static vector<PowerPlant*> powerplantCardsInGame;
