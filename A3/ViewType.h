#pragma once
#pragma once
#include "Observer.h"
#include "Game.h"

class ViewType : public Observer {
public:
	ViewType();
	ViewType(Game * game);
	virtual ~ViewType();

	virtual void printStatistics() = 0;
	virtual string getType();
	virtual void setType(string type);

private:
	string type;
	Game *subject; 

};