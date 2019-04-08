#pragma once
#include "Strategy.h"
#include "Player.h"
class AggressiveStrategy : public Strategy {
public:
	AggressiveStrategy();
	AggressiveStrategy(Player *p1);
	~AggressiveStrategy();
	void execute(Player*);
};