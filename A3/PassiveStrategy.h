#pragma once
#include "Strategy.h"
//passive player will always pass 
class PassiveStrategy : public Strategy {
public:
	PassiveStrategy();
	PassiveStrategy(Player *p);
	~PassiveStrategy();
	void execute(Player*);
};