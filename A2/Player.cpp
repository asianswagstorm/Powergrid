#include "Player.h"
#include "House.h"
#include "Resource.h"
#include "Powerplant.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

Player::Player() {
	this->name = "";
	this->area_color = "";
	this->electro = 50;
	this->house = 0;

	this->coal = 0;
	this->oil = 0;
	this->garbage = 0;
	this->uranium = 0;
}

Player::Player(string name, string area_color) {
	//Each player takes an overview card, the wooden houses of one color and 50 Elektro.
	//overview card = summary??
	this->name = name;
	this->area_color = area_color;
	this->electro = 50;
	this->house = 1;

	this->coal=0;
	this->oil=0;
	this->garbage=0;
	this->uranium=0;

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

int Player::getCoal() const {
	return coal;
}

void Player::setCoal(int coal) {
	this->coal = coal;
}

void Player::addCoal(int coal)
{
	this->coal += coal;
}

int Player::getOil() const {
	return oil;
}

void Player::setOil(int oil) {
	this->oil = oil;
}

void Player::addOil(int oil)
{
	this->oil += oil;
}

int Player::getGarbage() const {
	return garbage;
}

void Player::setGarbage(int garbage) {
	this->garbage = garbage;
}

void Player::addGarbage(int garbage)
{
	this->garbage += garbage;
}

int Player::getUranium() const {
	return uranium;
}
void Player::setUranium(int uranium) {
	this->uranium = uranium;
}

void Player::addUranium(int uranium)
{
	this->uranium += uranium;
}

void Player::printPlayerInfo() {
		std::cout << std::string("Name: ") << name << std::endl <<
		std::string("Electro: ") << electro << std::endl <<
		std::string("Houses: ") << house << std::endl <<
		std::string("Area Color: ") << area_color << std::endl <<
		std::string("Coal: ") << coal << std::endl <<
		std::string("Oil: ") << oil << std::endl <<
		std::string("Garbage: ") << garbage << std::endl <<
		std::string("Uranium: ") << uranium << std::endl;
		std::cout << std::endl;
}
