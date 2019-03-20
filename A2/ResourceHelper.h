#pragma once

#include "Coal.h"
#include "Oil.h"
#include "Garbage.h"
#include "Uranium.h"
#include <string>

class ResourceHelper {
public:
	ResourceHelper(); //Constructor
	~ResourceHelper(); //Destructor
	void edit(string type, int quantity, int cost); //Change function name to something more intuitive 
	void addResourceQuantity(string type, int quantity); //Cost is not important here

	void removeOneUnit(string resource); //Removes one unit of any resource at any index
	void remove(string resource, int qty); //Remove any quantity
	void addOneUnit(string resource); 
	int getResourceQuantity(string resource);
	int getResourceCost(string resource);

private:

	Coal * coal;
	Oil * oil;
	Garbage * garbage;
	Uranium * uranium;
};