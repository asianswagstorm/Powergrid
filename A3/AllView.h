#pragma once
#include "Statistics.h"
#include "Game.h"

class AllView : public Statistics {

public:
	AllView();
	AllView(Game * game);
	~AllView();

	//Implementing Abstract methods
	void Update();
	void printInfo();


};