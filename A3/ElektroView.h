#pragma once
#include "Statistics.h"
class ElektroView : public Statistics {
public:
	ElektroView();
	~ElektroView();
	ElektroView(Statistics * stats);

	void Update();
	void printInfo();

};