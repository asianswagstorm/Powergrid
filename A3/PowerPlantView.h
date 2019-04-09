#pragma once
#include "ViewDecorator.h"
class PowerPlantView : public ViewDecorator {
public:
	PowerPlantView();
	~PowerPlantView();
	PowerPlantView(View * decoratedView);
	void Update();
	void printInfo();

};