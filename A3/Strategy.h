#pragma once
#include "Player.h"

class Player;

class Strategy {
public:
	Strategy();
	~Strategy();
	virtual int execute(Player *p) { return -1; };
};