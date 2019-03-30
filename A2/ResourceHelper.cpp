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

void ResourceHelper::setResource(string type, int quantity) {

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
		return this->coal->getQuantity(); //null
	}

	if (resource == "Oil") {
		return this->oil->getQuantity();
	}

	if (resource == "Garbage") {
		return this->garbage->getQuantity();
	}

	if (resource == "Uranium") {
		return this->uranium->getQuantity();
	}

	else return -1;
}

int ResourceHelper::getResourceCost(string resource) {

	if (resource == "Coal") {
		return this->coal->getCost();
	}

	if (resource == "Oil") {
		return this->oil->getCost();
	}

	if (resource == "Garbage") {
		return this->garbage->getCost();
	}

	if (resource == "Uranium") {
		return this->uranium->getCost();
	}

	else return -1;

}

//void removeOneUnit(string resource); //Removes one unit of any resource at any index
void ResourceHelper::removeSingleResource(string resource) {

	if (resource == "Coal") {
		this->coal->removeQuantity(1);
	}

	if (resource == "Oil") {
		this->oil->removeQuantity(1);
	}

	if (resource == "Garbage") {
		this->garbage->removeQuantity(1);
	}

	if (resource == "Uranium") {
		this->uranium->removeQuantity(1);
	}
}

void ResourceHelper::remove(string resource, int qty) {

	if (resource == "Coal") {
		this->coal->removeQuantity(qty);
	}

	if (resource == "Oil") {
		this->oil->removeQuantity(qty);
	}

	if (resource == "Garbage") {
		this->garbage->removeQuantity(qty);
	}

	if (resource == "Uranium") {
		this->uranium->removeQuantity(qty);
	}
}

void ResourceHelper::addSingleResource(string resource) {

	if (resource == "Coal") {
		this->coal->addQuantity(1);
	}

	if (resource == "Oil") {
		this->oil->addQuantity(1);
	}

	if (resource == "Garbage") {
		this->garbage->addQuantity(1);
	}

	if (resource == "Uranium") {
		this->uranium->addQuantity(1);
	}

}
