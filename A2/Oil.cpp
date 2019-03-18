#include "Oil.h"

//Destructor
Oil::~Oil() {

}

//Default Constructor
Oil::Oil() {

    this->setColor("Black"); //Default color
    this->setQuantity(0); //Default amount
    setCost(0);
}

//Parameterized Constructor
Oil::Oil(int quantity)   {
    setCost(3);
    this->setColor("Black");
    setQuantity(quantity);
}

//Return type of resource
string Oil::getType() const {
    return type;
}

