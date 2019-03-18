#pragma once
#include<string>
#include <iostream>
#include "Resource.h"
#include "Powerplant.h"

using std::string;
class Player
{
public:
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

	int getCoal() const;
	void setCoal(int coal);
	void addCoal(int);

	int getOil() const;
	void setOil(int oil);
	void addOil(int);

	int getGarbage() const;
	void setGarbage(int garbage);
	void addGarbage(int);

	int getUranium() const;
	void setUranium(int uranium);
	void addUranium(int);

	void printPlayerInfo();

	int getNumberHouses();




private:
	string name;
	string area_color;
	int electro;
	int house;

	//resources
	int coal;
	int oil;
	int garbage;
	int uranium;

};
