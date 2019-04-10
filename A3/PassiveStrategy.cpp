#include "PassiveStrategy.h"

PassiveStrategy::PassiveStrategy() {}
PassiveStrategy::PassiveStrategy(Player *p) {
	execute(p);
}
PassiveStrategy::~PassiveStrategy() {}

// the passive player will always say no to everything
int PassiveStrategy::execute(Player*p) {
	return -1; }

