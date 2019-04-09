#include "Statistics.h"
#include "Game.h"

Statistics::Statistics() {
	this->type = "";
}
Statistics::Statistics(Game * game) {
	//Upon instantiation, attaches itself 
	//to a Game
	subject = game;
	subject->registerObserver(this);
	this->type = "";
}

Statistics::Statistics(Statistics * stats) {
	this->stats = stats;
}

Statistics::~Statistics() {
	subject->removeObserver(this);
}

string Statistics::getType() {
	return this->type;
}

void Statistics::setType(string type) {
	this->type = type;

}

//something notify