#include "Uranium.h"

//Destructor
Uranium::~Uranium() {
}

//Default Constructor
Uranium::Uranium() {

    this->setColor("Red"); //Default color
    this->setQuantity(0); //Default amount
    setCost(0);//Arbitrary Cost
}

//Parametrized Constructor
Uranium::Uranium(int quantity) {
    setCost(12);
    this->setColor("Red");
    setQuantity(quantity);
}


//Return type of resource
string Uranium::getType() const {
    return type;
}