#pragma once
#include "Statistics.h"
class PowerPlantView : public Statistics {
public:
	PowerPlantView();
	~PowerPlantView();
	PowerPlantView(Statistics * stats);
	void Update();
	void printInfo();

};