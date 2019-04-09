#include "ModerateStrategy.h"

ModerateStrategy::ModerateStrategy() {}
ModerateStrategy::ModerateStrategy(Player *p) {
	execute(p);
}
ModerateStrategy::~ModerateStrategy() {}


void ModerateStrategy::execute(Player*) {}

