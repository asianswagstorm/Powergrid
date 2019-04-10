#include "ModerateStrategy.h"

ModerateStrategy::ModerateStrategy() {}
ModerateStrategy::ModerateStrategy(Player *p) {
	execute(p);
}
ModerateStrategy::~ModerateStrategy() {}


int ModerateStrategy::execute(Player*) { return -1; }

