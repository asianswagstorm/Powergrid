#pragma once
#pragma once
#include "Observer.h"
class PowerPlantView : public Observer {
public:
	PowerPlantView();
	~PowerPlantView();

	void Update();
	void printInfo();

};