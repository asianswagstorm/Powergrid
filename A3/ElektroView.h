#pragma once
#include "Observer.h"
class ElektroView : public Observer {
public:
	ElektroView();
	~ElektroView();

	void Update();
	void printInfo();

};