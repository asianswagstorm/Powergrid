#include "ViewType.h"
#include "Game.h"

ViewType::ViewType() {
	this->type = "";
}
ViewType::ViewType(Game * game) {
	//Upon instantiation, attaches itself 
	//to a Game
	subject = game;
	subject->registerObserver(this);
	this->type = "";
}

ViewType::~ViewType() {
	subject->removeObserver(this);
}

string ViewType::getType() {
	return this->type;
}

void ViewType::setType(string type) {
	this->type = type;

}

//something notify