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
	void removeElectro(int);

	//house
	HouseHelper* getHouse() const;
	int getHouseCounter() const;
	bool hasEnoughtElektro(int amount);

	//powerplant
	vector<PowerPlant>* getPowerPlants() const;
	int getnumOfPowerPlants() const;
	void setnumOfPowerPlants(int numOfPowerPlants);
	
	void powerPowerPlant(int index); // bureaucracy fix
	
	void addPowerPlant(PowerPlant * powerplant); // adds a powerplant to the powerplants vector
	
	bool pass();//this one is used when the player chooses not to start an auction.
	bool auction(); //this one is used when the player chooses a power plant for auction.
	void resetAuction();
	bool getPass();
	bool getAuction();
	void setPass(bool);
	void setAuction(bool);
	//powerplanthelper add powerplant 	std::vector<PowerPlant>* powerplants;

	//resources 
	void setResources(string resource_type, int quantity); //Adds resource to player's possessions
	int getResourceQuantity(string resource_type) ;
	int getResourceCost(string resource_type) ;
	void printPlayerInfo();
	 
	bool validateResourcePurchase(int cost, int quantity, string type);
	int getTotalStorage();
	int getResourceStorage(string resource);

private:
	std::string name;
	std::string area_color;
	int electro;
	
	//powerplants
	int numOfPowerPlants;
	std::vector<PowerPlant>* powerplants;
	
	//houses
	HouseHelper* househelper;
	//resources
	ResourceHelper* resourcehelper;

	bool powerplantPurchased = false;
	bool hasAuction = false;
	
};
