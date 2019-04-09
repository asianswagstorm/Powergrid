#pragma once
#include "Statistics.h"
class ResourceView : public Statistics {
public:
	ResourceView();
	~ResourceView();
	ResourceView(Statistics * stats);
	void Update();
	void printInfo();

};