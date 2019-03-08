#include "Player.h"
Player::Player(string name, string area_color) {
	//Each player takes an overview card, the wooden houses of one color and 50 Elektro.
	this->name = name;
	this->area_color = area_color;
	electro = 50;
	house = 1;

	coal=0;
	oil=0;
	garbage=0;
	uranium=0;

}
Player::~Player() {

}
string Player::getName() {
	return name;
}
void Player::setName(string name) {
	this->name = name;
}

string Player::getAreaColor() {
	return area_color;
}
void Player::setAreaColor(string area_color) {
	this->area_color = area_color;
}

int Player::getHouse() {
	return house;
}

void Player::setHouse(int house) {
	this->house = house;
}

int Player::getElectro() {
	return electro;
}

void Player::setElectro(int electro) {
	this->electro = electro;
}

int Player::getCoal() {
	return coal;
}

void Player::setCoal(int coal) {
	this->coal = coal;
}

int Player::getOil() {
	return oil;
}

void Player::setOil(int oil) {
	this->oil = oil;
}

int Player::getGarbage() {
	return garbage;
}

void Player::setGarbage(int garbage) {
	this->garbage = garbage;
}

int Player::getUranium() {
	return uranium;
}
void Player::setUranium(int uranium) {
	this->uranium = uranium;
}

