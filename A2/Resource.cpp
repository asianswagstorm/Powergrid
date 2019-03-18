#include "Resource.h"

Resource::~Resource() {
}

//Default Constructor
Resource::Resource() {}

//Mutator Function to set the new amount of resources.
void Resource::setQuantity(int qty) {
    quantity = qty;
}

//Accessor function to return the amount of resources.
int Resource::getQuantity() const {
    return quantity;
}

//Muator function set the color of the resource.
void Resource::setColor(string color) {
    this->color = color;
}

//Accessor Function to return the color of the resource.
string Resource::getColor() const {
    return color;
}

//Variation of setQuantity but instead adds to the existing amount.
void Resource::addQuantity(int quantity) {
    this->quantity += quantity;
}

void Resource::removeQuantity(int quantity) {
    this->quantity -= quantity;
}

void Resource::setCost(int cost) {
    this->cost = cost;
}

int Resource::getCost()const {
    return cost;
}