#include "Coal.h"

//Destructor
Coal::~Coal() {

}

//Default Constructor
Coal::Coal() {
    setCost(0);
    this->setColor("Brown");
    this->setQuantity(0);
}

//Constructor for the quantity of coal
Coal::Coal(int quantity) {
    setCost(1); //round 1 
    this->setColor("Brown");
    setQuantity(quantity);
}

//Accessor function returning the type of resource
string Coal::getType() const {
    return type;
}

