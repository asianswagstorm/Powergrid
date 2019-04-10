#include "ModerateStrategy.h"

ModerateStrategy::ModerateStrategy() {}
ModerateStrategy::ModerateStrategy(Player *p) {
	execute(p);
}
ModerateStrategy::~ModerateStrategy() {}

//always perform an action
int ModerateStrategy::execute(Player*) {
	
	
	return -1; }

