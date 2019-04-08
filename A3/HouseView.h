#pragma once
#include "Observer.h"
class HouseView : public Observer {
public:
	HouseView();
	~HouseView();

	void Update();
	void printInfo();

};