#include "Player.h"
#include "House.h"
#include "Resource.h"
#include "Powerplant.h"
#include "ResourceHelper.h"
#include <string>
#include <iostream>


using std::cout;
using std::endl;

Player::Player() {
	this->name = "";
	this->area_color = "";
	this->electro = 50;
	powerplants = new vector<PowerPlant>();
	numOfPowerPlants = powerplants->size();
	this->househelper = new HouseHelper();
	this->resourcehelper = new ResourceHelper();
}

Player::Player(string name, string area_color, HouseHelper* househelper) {

	this->name = name;
	this->area_color = area_color;
	this->electro = 50;
	powerplants = new vector<PowerPlant>();
	numOfPowerPlants = powerplants->size();
	this->househelper = househelper;
	this->resourcehelper = new ResourceHelper();
	
}

Player::Player(string name,string area_color, int electro, HouseHelper * househelper, vector<PowerPlant> * powerplants, ResourceHelper * resourcehelper)
{
	this->area_color = area_color;
	this->electro = electro;
	this->househelper = househelper;
	this->powerplants = powerplants;
	numOfPowerPlants = powerplants->size();
	this->resourcehelper = resourcehelper;
}

Player::~Player() {

}
string Player::getName() const {
	return name;
}
void Player::setName(string name) {
	this->name = name;
}

string Player::getAreaColor() const {
	return area_color;
}
void Player::setAreaColor(string area_color) {
	this->area_color = area_color;
}

int Player::getElectro() const {
	return electro;
}

void Player::setElectro(int electro) {
	this->electro = electro;
}

void Player::addElectro(int electro)
{
	this->electro += electro;
}

HouseHelper* Player::getHouse() const 
{
	return this->househelper;

}

int Player::getHouseCounter() const 
{
	return this->househelper->getHouse();
}

vector<PowerPlant>* Player::getPowerPlants() const
{
	return this->powerplants;
}

int Player::getnumOfPowerPlants() const
{
	return this->numOfPowerPlants;
}

void Player::setnumOfPowerPlants(int numOfPowerPlants)
{
	this->numOfPowerPlants = numOfPowerPlants;
}

void Player::setResources(string resource_type, int quantity)  { //Adds resource to player's possessions
	resourcehelper->setResource(resource_type, quantity);
}

int Player::getResourceQuantity(string resource_type)  {
	return resourcehelper->getResourceQuantity(resource_type);
}

int Player::getResourceCost(string resource_type) {
	return resourcehelper->getResourceCost(resource_type);

}

void Player::printPlayerInfo() {
		std::cout << std::string("Name: ") << name << std::endl <<
		std::string("Electro: ") << electro << std::endl <<
		std::string("Houses: ") << Player::getHouseCounter() << std::endl <<
		std::string("PowerPlants: ") << Player::getnumOfPowerPlants() << std::endl <<
		std::string("Area Color: ") << area_color << std::endl <<
		std::string("Coal: ") << Player::getResourceQuantity("Coal") << std::endl <<
		std::string("Oil: ") << Player::getResourceQuantity("Oil") << std::endl <<
		std::string("Garbage: ") << Player::getResourceQuantity("Garbage") << std::endl <<
		std::string("Uranium: ") << Player::getResourceQuantity("Uranium") << std::endl;

		std::cout << std::endl;
}
