#pragma once
#include "ViewDecorator.h"
class HouseView : public ViewDecorator {
public:
	HouseView();
	~HouseView();
	HouseView(View * decoratedView);
	void Update();
	void printInfo();

};