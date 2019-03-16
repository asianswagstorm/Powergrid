#include <iostream>
#include <string>
#include "House.h";

using namespace std;

//Default constructor
House::House(){
    index = 0; //arbitrary index
    location = ""; //arbitrary location
}

//Destructor
House::~House(){

}

//Constructor initializes house location
House::House(int index, string location){
    this->index = index;
    this->location = location;
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
    return location;
}
