#include "PassiveStrategy.h"

PassiveStrategy::PassiveStrategy() {}
PassiveStrategy::PassiveStrategy(Player *p) {
	execute(p);
}
PassiveStrategy::~PassiveStrategy() {}


void PassiveStrategy::execute(Player*) {}

