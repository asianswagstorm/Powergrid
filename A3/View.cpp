#include "View.h"
#include "Game.h"

View::View() {
	this->type = "";
}
View::View(Game * game) {
	//Upon instantiation, attaches itself 
	//to a Game
	subject = game;
	subject->registerObserver(this);
	this->type = "";
}

View::~View() {
	subject->removeObserver(this);
}

string View::getType() {
	return this->type;
}

void View::setType(string type) {
	this->type = type;

}
