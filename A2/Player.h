#pragma once
#include<string>
#include <iostream>
#include "Resource.h"
#include "PowerPlant.h"
#include "HouseHelper.h"
#include "ResourceHelper.h"

using std::string;
class Player
{
public:
	Player();
	Player(string name, string area_color, HouseHelper* househelper);
	Player(string name, string area_color, int elektro, HouseHelper * househelper, vector<PowerPlant> * powerplants, ResourceHelper * resourcehelper);
	~Player();
	
	string getName() const;
	void setName(string name);

	string getAreaColor() const;
	void setAreaColor(string area_color);

	int getElectro() const;
	void setElectro(int electro);
	void addElectro(int);

	HouseHelper* getHouse() const;
	int getHouseCounter() const;

	//resources 
	void setResources(string resource_type, int quantity); //Adds resource to player's possessions
	int getResourceQuantity(string resource_type) ;
	int getResourceCost(string resource_type) ;
	void printPlayerInfo();

	//void pass();//this one is used when the player chooses not to start an auction.
	//void auction(); //this one is used when the player chooses a power plant for auction.

private:
	std::string name;
	std::string area_color;
	int electro;
	
	//powerplants
	int powerPlantCounter;
	std::vector<PowerPlant>* powerplants;
	//houses
	HouseHelper* househelper;
	//resources
	ResourceHelper* resourcehelper;

};
