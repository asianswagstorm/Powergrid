#pragma once
#pragma once
#include "Observer.h"
#include "Game.h"

class Statistics : public Observer {
public:
	Statistics();
	Statistics(Game * game); //for phase observer
	Statistics(Statistics * stats); // for game statistics observer
	virtual ~Statistics();

	virtual void printInfo() = 0;
	virtual string getType();
	virtual void setType(string type);
	Game * subject;
private:
	string type;
	Statistics * stats;
};