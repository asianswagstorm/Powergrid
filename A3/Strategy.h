#pragma once
#include "Player.h"

class Player;

class Strategy {
public:
	Strategy();
	~Strategy();
	virtual void execute(Player *p) {};
};