#pragma once
#include "Strategy.h"

class RandomStrategy : public Strategy {
public:
	RandomStrategy();
	RandomStrategy(Player *p);
	~RandomStrategy();
	int execute(Player*);
};