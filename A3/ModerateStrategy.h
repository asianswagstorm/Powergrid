#pragma once
#include "Strategy.h"

class ModerateStrategy : public Strategy {
public:
	ModerateStrategy();
	ModerateStrategy(Player *p);
	~ModerateStrategy();
	int execute(Player*);
};