#include "ResourceMarket.h"
#include "ResourceHelper.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

//the constructor initializes game resources
ResourceMarket::ResourceMarket() {
	//round1
	market[0] = new ResourceHelper();
	market[0]->edit("Coal", 3, 1); //edit(type,quantity in market,cost)
	market[0]->edit("Oil", 0, 1);
	market[0]->edit("Garbage", 0, 1);
	market[0]->edit("Uranium", 0, 1);
	//round2
	market[1] = new ResourceHelper();
	market[1]->edit("Coal", 3, 2);
	market[1]->edit("Oil", 0, 2);
	market[1]->edit("Garbage", 0, 2);
	market[1]->edit("Uranium", 0, 2);
	//round3
	market[2] = new ResourceHelper();
	market[2]->edit("Coal", 3, 3);
	market[2]->edit("Oil", 3, 3);
	market[2]->edit("Garbage", 0, 3);
	market[2]->edit("Uranium", 0, 3);
	//round4
	market[3] = new ResourceHelper();
	market[3]->edit("Coal", 3, 4);
	market[3]->edit("Oil", 3, 4);
	market[3]->edit("Garbage", 0, 4);
	market[3]->edit("Uranium", 0, 4);
	//round5
	market[4] = new ResourceHelper();
	market[4]->edit("Coal", 3, 5);
	market[4]->edit("Oil", 3, 5);
	market[4]->edit("Garbage", 0, 5);
	market[4]->edit("Uranium", 0, 5);
	//round6
	market[5] = new ResourceHelper();
	market[5]->edit("Coal", 3, 6);
	market[5]->edit("Oil", 3, 6);
	market[5]->edit("Garbage",0, 6);
	market[5]->edit("Uranium", 0, 6);
	//round7
	market[6] = new ResourceHelper();
	market[6]->edit("Coal", 3, 7);
	market[6]->edit("Oil", 3, 7);
	market[6]->edit("Garbage", 3, 7);
	market[6]->edit("Uranium", 0, 7);
	//round8
	market[7] = new ResourceHelper();
	market[7]->edit("Coal", 3, 8);
	market[7]->edit("Oil", 3, 8);
	market[7]->edit("Garbage", 3, 8);
	market[7]->edit("Uranium", 0, 8);
	//round9
	market[8] = new ResourceHelper();
	market[8]->edit("Uranium", 1, 10);
	//round10
	market[9] = new ResourceHelper();
	market[9]->edit("Uranium", 1, 12);
	//round11
	market[10] = new ResourceHelper();
	market[10]->edit("Uranium", 1, 14);
	//round12
	market[11] = new ResourceHelper();
	market[11]->edit("Uranium", 1, 16);

}

//Destructor
ResourceMarket::~ResourceMarket() {

}

//Removes resources purchased by players during phase 3
void ResourceMarket::updateMarket(string resource, int quantity) {

	for (int i = 0; i <= 11; i++) {

		while (market[i]->getResourceQuantity(resource) != 0) {//ResourceHelper::getResourceQuantity(string resource) 
			market[i]->removeSingleResource(resource);//removeOneUnit
			quantity--;
			if (quantity == 0)
				break;
		}
		if (quantity == 0)
			break;
	}
}

//Return total quantity of resource in market
int ResourceMarket::getMarketQuantity(string resource) {

	int amount_in_market = 0;

	for (int i = 0; i <= 11; i++) {
		amount_in_market += market[i]->getResourceQuantity(resource); // no change
	}
	return amount_in_market;
}

//Resource Table how many resources to resupply On the back of game rules 
void ResourceMarket::refill(int step, int playerSize) {
                                       
	int numCoal, numOil, numGarbage, numUranium;

	switch(playerSize)
	{
		case 2:
		if (step == 1) 
		{
			numCoal = 3;
			numOil = 2;
			numGarbage = 1;
			numUranium = 1;
		} 
	   else if (step == 2) 
		{
			numCoal = 4;
			numOil = 2;
			numGarbage = 2;
			numUranium = 1;
		}
	   else if (step == 3) 
		{
			numCoal = 3;
			numOil = 4;
			numGarbage = 3;
			numUranium = 1;
		}
		break; 
	
		case 3:
		if (step == 1) 
		{
			numCoal = 4;
			numOil = 2;
			numGarbage = 1;
			numUranium = 1;
		}
		else if (step == 2) 
		{
			numCoal = 5;
			numOil = 3;
			numGarbage = 2;
			numUranium = 1;
		}
		else if (step == 3)
		{
			numCoal = 3;
			numOil = 4;
			numGarbage = 3;
			numUranium = 1;
		}
		break;
		
		case 4:
		if (step == 1) 
		{
			numCoal = 5;
			numOil = 3;
			numGarbage = 2;
			numUranium = 1;
		}
		else if (step == 2) 
		{
			numCoal = 6;
			numOil = 4;
			numGarbage = 3;
			numUranium = 2;
		}
		else if (step == 3)
		{
			numCoal = 4;
			numOil = 5;
			numGarbage = 4;
			numUranium = 2;
		}
		break;
		
		case 5:
		if (step == 1)
		{
			numCoal = 5;
			numOil = 4;
			numGarbage = 3;
			numUranium = 2;
		}
		else if (step == 2)
		{
			numCoal = 7;
			numOil = 5;
			numGarbage = 3;
			numUranium = 3;
		}
		else if (step == 3)
		{
			numCoal = 5;
			numOil = 6;
			numGarbage = 5;
			numUranium = 2;
		}
		break;
		
		case 6:
		if (step == 1)
		{
			numCoal = 7;
			numOil = 5;
			numGarbage = 3;
			numUranium = 2;
		}
		else if (step == 2)
		{
			numCoal = 9;
			numOil = 6;
			numGarbage = 5;
			numUranium = 3;
		}
		else if (step == 3)
		{
			numCoal = 6;
			numOil = 7;
			numGarbage = 6;
			numUranium = 3;	
		}
		break;
		
		default:
		std::cout << " Invalid number of players! " << std::endl;
		break;
	}
		if (step == 1 || step == 2 || step == 3) {
			ResourceMarket::refillHelper("Coal",numCoal);
			ResourceMarket::refillHelper("Oil", numOil);
			ResourceMarket::refillHelper("Garbage", numGarbage);
			ResourceMarket::refillHelper("Uranium", numUranium);
		}

		else if (step != 1 && step != 2 && step != 3) {
			cout << "NOT step 1,2,3" << endl;
			system("pause");
		}

}

//Refill the market according to the last page 
void ResourceMarket::refillHelper(string resource, int quantity) {

		for (int i = 0; i < 8; i++) { 

			while (market[i]->getResourceQuantity(resource) < 3) { //getResourceQuantity?????
				market[i]->addSingleResource(resource);
				quantity--;
				if (quantity == 0)
					break;
			}
			if (quantity == 0)
				break;
		}
	
	//Replenishing Uranium only round 9 to 12
	if (resource == "Uranium") {
		for (int i = 8; i < 12; i++) { 
			
			while (market[i]->getResourceQuantity(resource) < 1) { //why???
				market[i]->addSingleResource(resource);//addOneUnit
				quantity--;
			
				if (quantity == 0)
					break;
			}
			if (quantity == 0)
				break;
		}
	}

}

//It returns current cost of an valid quantity of a resource
int ResourceMarket::getMarketCost(string resource, int quantity) {
	cout << "The market only has " << this->getMarketQuantity(resource) <<endl;
	if (quantity > this->getMarketQuantity(resource)) {
		cout << "The market only has " << this->getMarketQuantity(resource) << " " << resource << " Inssuficient quantity "<< endl;
		return -1;
	}

	//loop through market and get price.
	/*
	//The following are helper counters for the functionality of the method
	int i = 0;
	
	int counter = 0;
	bool insideIndex = true;

	//The cost of the resource
	int cost = 0;
	//The following two if statements allow us to start at the proper resource slot
	if (i1 != -1)
		i = i1;

	else if (i2 != -1)
		i = i2;

	//Looping through market to find cost the desired quantity
	while (quantity != 0) {
		insideIndex = true;
		int amountAtIndex = market[i + counter]->getResourceQuantity(resource);

		while (insideIndex) {

			if (amountAtIndex != 0) {
				cost += market[i + counter]->getResourceCost(resource); //Computing cost of 1 unit at that index
				quantity -= 1; //Getting the cost of 1 resource at a time
				amountAtIndex--;

				if (quantity == 0)
					return cost;
			}
			else {
				counter++; //Move to next slot
				insideIndex = false; //No longer inside current slot
			}
		} //End of inner while

	}//End of while
	return cost;
	*/
	return 1; // set cost as 1 for now
}

void ResourceMarket::showInfo() {

	for (int i = 0; i <= 11; i++) {

		cout << "Slot[" << i << "]: " << "Coal, Oil, Garbage, Uranium" << endl << "Quantity: " <<
			market[i]->getResourceQuantity("Coal") << ",  " <<
			market[i]->getResourceQuantity("Oil") << ",  " <<
			market[i]->getResourceQuantity("Garbage") << ",  " <<
			market[i]->getResourceQuantity("Uranium") << "  " << endl << "Price: " << market[i]->getResourceCost("Uranium") << endl << endl;
	}

}

int ResourceMarket::getTotal(string resource) {
	//WRONG ITS ADDING EVERYTHING. from 12 rounds 
	int quantity = 0;

	if (resource == "Uranium") {
		for (int i = 0; i <= 11; i++)
			quantity += market[i]->getResourceQuantity(resource);
		return quantity;
	}

	for (int i = 0; i <= 7; i++)
		quantity += market[i]->getResourceQuantity(resource);

	return quantity;
}

void ResourceMarket::showRemaining() {
	std::cout << "Here is what is in the resource market: " << std::endl;
	std::cout << std::endl << "Remaining Coal in Market: " << getTotal("Coal") << std::endl
		<< "Remaining Oil in Market: " << getTotal("Oil") << std::endl
		<< "Remaining Garbage in Market: " << getTotal("Garbage") << std::endl
		<< "Remaining Uranium in Market: " << getTotal("Uranium") << std::endl;

}
