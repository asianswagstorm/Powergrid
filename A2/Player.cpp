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
	this->house = 0;

	this->resources = new ResourceHelper();
}

Player::Player(string name, string area_color) {
	//Each player takes an overview card, the wooden houses of one color and 50 Elektro.
	//overview card = summary??
	this->name = name;
	this->area_color = area_color;
	this->electro = 50;
	this->house = 1;

	this->resources = new ResourceHelper();

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

int Player::getHouse() const {
	return house;
}

void Player::setHouse(int house) {
	this->house = house;
}

void Player::addHouse(int house)
{
	this->house += house;
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


void Player::addResources(string resource_type, int quantity)  { //Adds resource to player's possessions
	resources->addResourceQuantity(resource_type, quantity);
}

int Player::getResourceQuantity(string resource_type)  {
	return resources->getResourceQuantity(resource_type);
}

int Player::getResourceCost(string resource_type) {
	return resources->getResourceCost(resource_type);

}

void Player::printPlayerInfo() {
		std::cout << std::string("Name: ") << name << std::endl <<
		std::string("Electro: ") << electro << std::endl <<
		std::string("Houses: ") << house << std::endl <<
		std::string("Area Color: ") << area_color << std::endl <<
		std::string("Coal: ") << Player::getResourceQuantity("Coal") << std::endl <<
		std::string("Oil: ") << Player::getResourceQuantity("Oil") << std::endl <<
		std::string("Garbage: ") << Player::getResourceQuantity("Garbage") << std::endl <<
		std::string("Uranium: ") << Player::getResourceQuantity("Uranium") << std::endl;
		std::cout << std::endl;
}
