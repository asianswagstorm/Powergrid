#ifndef PART3_RESOURCE_H
#define PART3_RESOURCE_H

#include <string>
#include <iostream>

using namespace std;

//Abstract class where the four resources will inherit from
class Resource {

public:

    virtual ~Resource();
    Resource();

    void setQuantity(int qty);
    void addQuantity(int qty);
    void removeQuantity(int qty);
    int getQuantity() const;
    void setColor(string color);
    string getColor() const;

    //Virtual functions
    virtual int getCost() const;
    virtual void setCost(int cost);
    virtual string getType()const = 0; //Pure Virtual Function


private:
    int cost;
    int quantity; //Amount of resources
    string color; //Color of the resource object
};

#endif //PART3_RESOURCE_H
