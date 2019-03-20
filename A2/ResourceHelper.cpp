#include "ResourceHelper.h"

ResourceHelper::ResourceHelper() {
	
	coal = new Coal();
	oil = new Oil();
	garbage = new Garbage();
	uranium = new Uranium();

}

ResourceHelper::~ResourceHelper() {
	delete coal;
	delete oil;
	delete garbage;
	delete uranium;
}

void ResourceHelper::edit(string type, int quantity, int cost) {

	if (type == "Coal") {
		coal->setCost(cost);
		coal->setQuantity(quantity);
	}

	if (type == "Oil") {
		oil->setCost(cost);
		oil->setQuantity(quantity);
	}

	if (type == "Garbage") {
		garbage->setCost(cost);
		garbage->setQuantity(quantity);
	}

	if (type == "Uranium") {
		uranium->setCost(cost);
		uranium->setQuantity(quantity);
	}

}

void ResourceHelper::addResourceQuantity(string type, int quantity) {

	if (type == "Coal")
		coal->addQuantity(quantity);

	if (type == "Oil")
		oil->addQuantity(quantity);

	if (type == "Garbage")
		garbage->addQuantity(quantity);

	if (type == "Uranium")
		uranium->addQuantity(quantity);

}

int ResourceHelper::getResourceQuantity(string resource) {
	if (resource == "Coal") {
		return coal->getQuantity();
	}

	if (resource == "Oil") {
		return oil->getQuantity();
	}

	if (resource == "Garbage") {
		return garbage->getQuantity();
	}

	if (resource == "Uranium") {
		return uranium->getQuantity();
	}

	else return -1;
}

int ResourceHelper::getResourceCost(string resource) {

	if (resource == "Coal") {
		return coal->getCost();
	}

	if (resource == "Oil") {
		return oil->getCost();
	}

	if (resource == "Garbage") {
		return garbage->getCost();
	}

	if (resource == "Uranium") {
		return uranium->getCost();
	}

	else return -1;

}

//void removeOneUnit(string resource); //Removes one unit of any resource at any index
void ResourceHelper::removeOneUnit(string resource) {

	if (resource == "Coal") {
		coal->removeQuantity(1);
	}

	if (resource == "Oil") {
		oil->removeQuantity(1);
	}

	if (resource == "Garbage") {
		garbage->removeQuantity(1);
	}

	if (resource == "Uranium") {
		uranium->removeQuantity(1);
	}
}

void ResourceHelper::remove(string resource, int qty) {

	if (resource == "Coal") {
		coal->removeQuantity(qty);
	}

	if (resource == "Oil") {
		oil->removeQuantity(qty);
	}

	if (resource == "Garbage") {
		garbage->removeQuantity(qty);
	}

	if (resource == "Uranium") {
		uranium->removeQuantity(qty);
	}
}

//Need multiple ifs in order to catch an error
void ResourceHelper::addOneUnit(string resource) {

	if (resource == "Coal") {
		coal->addQuantity(1);
	}

	if (resource == "Oil") {
		oil->addQuantity(1);
	}

	if (resource == "Garbage") {
		garbage->addQuantity(1);
	}

	if (resource == "Uranium") {
		uranium->addQuantity(1);
	}

}
