#include "Garbage.h"

//Destructor
Garbage::~Garbage() {

}

//Default Constructor
Garbage::Garbage() {
    setCost(0);
    this->setColor("Yellow"); //Defautl Color
    this->setQuantity(0); //Default amount
}

//Parameterized Constructor
Garbage::Garbage(int quantity) {
    setCost(8);
    this->setColor("Yellow");
    setQuantity(quantity);
}


//Returns type of resource
string Garbage::getType() const {
    return type;
}
