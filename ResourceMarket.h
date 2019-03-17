#ifndef PART3_RESOURCEMARKET_H
#define PART3_RESOURCEMARKET_H
#include "ResourceManager.h"
#include "Coal.h"
#include "Oil.h"
#include "Garbage.h"
#include "Uranium.h"

//This class is the resource market that holds all four resources that players will buy from
class ResourceMarket {

public:
    ResourceMarket();
    ~ResourceMarket();

    int getMarketCost(string resource, int quantity); //Returns cost of any quantity of a resource.
    int getMarketQuantity(string resource); //Return total quantity of resource currently in market

    void saveMarket(); // Saves ResourceMarket to resourcemarket.txt file
    void loadMarket(); // Loads ResourceMarket from resourcemarket.txt file
    void updateMarket(string resource, int quantity); //Removes resources purchased by players during phase 3
    void showInfo();

    void showRemaining();
    int getTotal(string resource);
    void refill(int step, int players); //Refills the resource market according to step and number of players

private:
    ResourceManager * market[12];

    //Internal Behaviour Methods that should not be accessed outside of class
    int findEmpty(string resource); //Finds the last index that is empty, this will be the index used to refill the resource
    int findPartial(string resource); //Finds the last index that is not full but not empty
    void replenish(string resource, int quantity); //Quantity to be filled

};

#endif //PART3_RESOURCEMARKET_H
