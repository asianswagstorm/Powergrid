#include "Player.h"
#include "House.h"
#include "Resource.h"
#include "PowerPlant.h"
#include "PowerPlantHelper.h"
#include "ResourceHelper.h"
#include <string>
#include <iostream>


using std::cout;
using std::endl;

Player::Player(Strategy *strat) { //default
	this->strat = strat;
	this->name = "";
	this->area_color = "";
	this->electro = 50;
	powerplants = new vector<PowerPlant>();
	numOfPowerPlants = powerplants->size();
	this->househelper = new HouseHelper();
	this->resourcehelper = new ResourceHelper();

}
Player::Player(Player *p, Strategy *strat) {
	this->strat = strat;
	this->name = p->name;
	this->area_color = p->area_color;
	this->electro = p->electro;
	powerplants = p->powerplants;
	numOfPowerPlants = p->numOfPowerPlants;
	this->househelper = p->househelper;
	this->resourcehelper = p->resourcehelper;
}
void Player::setStrategy(Strategy *strat) {
	this->strat = strat;
}
int Player::executeStrategy() {
	return this->strat->execute(this);
}

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

void Player::removeElectro(int electro)
{
	this->electro -= electro;
}


HouseHelper* Player::getHouse() const 
{
	return this->househelper;

}

int Player::getHouseCounter() const 
{
	return this->househelper->getHouse();
}

vector<PowerPlant>* Player::getPowerPlants()
{
	return this->powerplants; //returns the vector of powerplants
}

int Player::getnumOfPowerPlants() const
{
	return this->powerplants->size();
	
}

void Player::setnumOfPowerPlants(int numOfPowerPlants)
{
	this->numOfPowerPlants = numOfPowerPlants;
}

void Player::addPowerPlant(PowerPlant powerplant)
{
	//this is giving me bugs
	//During the game each player can have only 3 power plants at any time. (from game rule) , // if powerplant vector is full
	/*if (this->powerplants->size() == 3) {
		std::cout << std::endl << "ERROR YOU ALREADY HAVE MAXIMUM POWERPLANT" << std::endl;
		std::cout << "You must replace one of your powerplants before adding a new one." << std::endl;
		for (int i = 0; i < 3; i++) { 
			std::cout << i + 1 << ": ";
			(*powerplants)[i].printPowerPlantSummary(); 
			std::cout << std::endl;
		}
		int ppToBeRemoved = -1;
		std::cout << std::endl << "Enter the powerplant number you wish to remove:" << std::endl;
		
		while (ppToBeRemoved < 1 && ppToBeRemoved > 3) {
			cin >> ppToBeRemoved;
			if (ppToBeRemoved < 1 || ppToBeRemoved > 3)
				std::cout << "Invalid Input (must be between 1 - 3): " << std::endl;
			else
				break;
		}
		this->powerplants->erase(this->powerplants->begin() + (ppToBeRemoved-1));
		this->powerplants->push_back(powerplant);	
	}
	else{*/
		
	//for (unsigned int i = 0; i < powerplants->size(); i++) {
		//if ((*powerplants)[i].getTypeNum() != powerplant.getTypeNum()) { //prevent duplicates
			this->powerplants->push_back(powerplant);
			Player::setnumOfPowerPlants(Player::getnumOfPowerPlants());
		//}
		//}
		
	//}
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

//this one is used when the player chooses not to start an auction.
bool  Player::pass() {
	Player::powerplantPurchased = true;
	return powerplantPurchased;
}

//this one is used when the player chooses a power plant for auction.
bool  Player::auction() {
	this->Player::setAuction(true);
	return hasAuction;
}

bool  Player::getPass() {
	return Player::powerplantPurchased;
}

bool Player::getAuction() {
	return hasAuction;
}

void  Player::setPass(bool powerplantPurchased) {
	this->powerplantPurchased = powerplantPurchased;

}
void  Player::setAuction(bool hasAuction) {
	this->hasAuction = hasAuction;
}

void Player::resetAuction() {
	this->Player::setPass(false);
	this->Player::setAuction(false);
}

//Resources
//validates the resources that we purchased
bool Player::validateResourcePurchase(int cost, int quantity, string type) {

	if (this->getElectro() < cost) {
		std::cout << "Not enough elektros to purchase resources!" << std::endl;
		return false;
	}

	if (type != "Coal" && type != "Oil" && type != "Garbage" && type != "Uranium") {
		std::cout << "Invalid resource type!" << std::endl;
		return false;
	}
	
	//let user buy resource.
	this->setResources(type, quantity);
	this->removeElectro(cost);
	return true;
}

// Check if the player has enough money to buy a house
bool Player::hasEnoughtElektro(int amount) {

	int temp = this->electro;
	if ((temp - amount) >= 0) {
		return true;
	}
	return false;
}

void Player::powerPowerPlant(int pNumber) {
	PowerPlantHelper * pp = new PowerPlantHelper();

	int index = pp->findPowerPlant(pNumber);
	string type = pp->getPlantType(index);
	int amount = pp->getPlantResources(index);
	if (type == "Hybrid") {

		string choice;
		if (getResourceQuantity("Coal") >= amount && getResourceQuantity("Oil") >= amount) {

			while (choice != "Oil" && choice != "oil" && choice != "Coal" && choice != "coal") {
				cout << "Would you like to remove " << amount << " units of Coal or Oil? ";
				cin >> choice;

				if (choice == "Oil" || choice == "oil") {
					this->resourcehelper->remove("Oil", amount);
				}

				if (choice == "Coal" || choice == "coal") {
					this->resourcehelper->remove("Coal", amount);
				}
				cout << endl;
			}
		}

		else if (getResourceQuantity("Coal") >= amount) {
			choice = "Coal";
			this->resourcehelper->remove(choice, amount);
		}

		else if (getResourceQuantity("Oil") >= amount) {
			choice = "Oil";
			this->resourcehelper->remove(choice, amount);
		}

		cout << "Removed(hybrid) " << amount << " units of " << choice << endl;
		delete pp;
		return;
	}

	if (type == "Eco") {
		delete pp;
		return;
	}

	this->resourcehelper->remove(type, amount);

	cout << "Removed " << amount << " units of " << type << endl;

	delete pp; //Freeing heap

}

