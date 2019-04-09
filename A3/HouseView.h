#pragma once
#include "Statistics.h"
class HouseView : public Statistics {
public:
	HouseView();
	~HouseView();
	HouseView(Statistics * stats);
	void Update();
	void printInfo();

};