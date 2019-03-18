#include <iostream>
#include <string>
#include "House.h";

using namespace std;

//Default constructor
House::House(){
    index = 0; //arbitrary index
    location = ""; //arbitrary location
	house_color = "";
}

//Destructor
House::~House(){

}

//Constructor initializes house location
House::House(int index, string location , string house_color){
    this->index = index;
    this->location = location;
	this->house_color = house_color;
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
