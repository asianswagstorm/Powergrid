#include <iostream>
#include <string>
#include "House.h"

using namespace std;

//Default constructor
House::House(){
    this->index = 0; //arbitrary index
    this->location = ""; //arbitrary location
	this->house_color = "";
	this->isPowered = false;
}

House::House(int index, string location) {
	this->index = index;
	this->location = location;
	this->isPowered = false;
}
//Constructor initializes house location
House::House(int index, string location , string house_color){
    this->index = index;
    this->location = location;
	this->house_color = house_color;
	this->isPowered = false;
}

//Destructor
House::~House() {

}

int House::getIndex()
{
    return index;
}

void House::setIndex(int index)
{
    this->index = index;
}

//Mutator function to set location of house
void House::setLocation(string location){
    this->location = location;
}

//Acccessor function to get location of house
string House::getLocation(){
    return this->location;
}

void House::setHouseColor(string house_color) {
	this->house_color = house_color;
}

//Acccessor function to get location of house
string House::getHouseColor() {
	return this->house_color;
}

bool House::getisPowered() {
	return this->isPowered;

}
void House::setisPowered(bool isPowered) {
	this->isPowered = isPowered;
}