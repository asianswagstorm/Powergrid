#include "AggressiveStrategy.h"

AggressiveStrategy::AggressiveStrategy() {}
AggressiveStrategy::AggressiveStrategy(Player *p) {
	execute(p);
}
AggressiveStrategy::~AggressiveStrategy() {}


void AggressiveStrategy::execute(Player*) {}

