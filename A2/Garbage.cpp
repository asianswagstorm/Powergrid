#include "Garbage.h"

//Destructor
Garbage::~Garbage() {

}

//Default Constructor
Garbage::Garbage() {
    setCost(0);
    this->setColor("Yellow"); //Default Color
    this->setQuantity(0); //Default amount
}

//Constructor for quantity of Garbage
Garbage::Garbage(int quantity) {
    setCost(7); 
    this->setColor("Yellow");
    setQuantity(quantity);
}


//Returns type of resource
string Garbage::getType() const {
    return resource_type;
}


