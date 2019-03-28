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
	void setResource(string type, int quantity); 

	void removeSingleResource(string resource); 
	void remove(string resource, int quantity); 
	void addSingleResource(string resource);
	int getResourceQuantity(string resource);
	int getResourceCost(string resource);

private:
	Coal * coal;
	Oil * oil;
	Garbage * garbage;
	Uranium * uranium;
};