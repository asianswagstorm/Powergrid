#pragma once
#include "View.h"
class HouseView : public View {
public:
	HouseView();
	~HouseView();
	HouseView(View * view);
	void Update();
	void printInfo();

};