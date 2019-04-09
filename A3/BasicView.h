#pragma once
#include "View.h"
#include "Game.h"

class BasicView : public View {

public:
	BasicView();
	BasicView(Game * game);
	~BasicView();

	//Abstract methods
	void Update();
	void printInfo();
};