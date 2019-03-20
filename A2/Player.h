#pragma once
#include<string>
#include <iostream>
#include "Resource.h"
#include "Powerplant.h"
#include "ResourceHelper.h"



using std::string;
class Player
{
public:
	Player();
	Player(string name, string area_color);
	//Player(string area_color, int electro, HouseManager *hm, vector<Powerplant> *pp, ResourceManager *rm);
	~Player();
	
	string getName() const;
	void setName(string name);

	string getAreaColor() const;
	void setAreaColor(string area_color);

	int getElectro() const;
	void setElectro(int electro);
	void addElectro(int);

	int getHouse() const;
	void setHouse(int house);
	void addHouse(int);
	
	//resources 
	void addResources(string resource_type, int quantity); //Adds resource to player's possessions
	int getResourceQuantity(string resource_type) ;
	int getResourceCost(string resource_type) ;
	void printPlayerInfo();


	//int getNumberHouses();

private:
	string name;
	string area_color;
	int electro;
	int house;

	//resources
	ResourceHelper* resources;

};
