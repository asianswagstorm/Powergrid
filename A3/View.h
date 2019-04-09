#pragma once
#pragma once
#include "Observer.h"
#include "Game.h"
//Abstract
class View : public Observer {
public:
	View();
	View(Game * game); //for phase observer
	virtual ~View();

	virtual void printInfo() = 0;
	virtual string getType();
	virtual void setType(string type);
	Game * subject;
private:
	string type;
	
};