#pragma once
#include "Strategy.h"

class AggressiveStrategy : public Strategy {
public:
	AggressiveStrategy();
	AggressiveStrategy(Player *p);
	~AggressiveStrategy();
	void execute(Player*);
};