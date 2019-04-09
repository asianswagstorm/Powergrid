#pragma once
#include "View.h"
class PowerPlantView : public View {
public:
	PowerPlantView();
	~PowerPlantView();
	PowerPlantView(View * view);
	void Update();
	void printInfo();

};