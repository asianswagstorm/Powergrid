#pragma once
#include<string>
using std::string;
class Player
{
public:
	Player(string name, string area_color);
	~Player();
	
	string getName();
	void setName(string name);

	string getAreaColor();
	void setAreaColor(string area_color);

	int getElectro();
	void setElectro(int electro);

	int getHouse();
	void setHouse(int house);

	int getCoal();
	void setCoal(int coal);
	
	int getOil();
	void setOil(int oil);

	int getGarbage();
	void setGarbage(int garbage);

	int getUranium();
	void setUranium(int uranium);

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
