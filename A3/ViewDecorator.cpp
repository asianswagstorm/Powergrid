#include "ViewDecorator.h"
#include <iostream>
using namespace std;
ViewDecorator::ViewDecorator() {
}

ViewDecorator::ViewDecorator(View * view) {
	this->decoratedView = view;
}

ViewDecorator::~ViewDecorator() {
	delete decoratedView;
}
