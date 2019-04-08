#pragma once
#include "Observer.h"
class ResourceView : public Observer {
public:
	ResourceView();
	~ResourceView();

	void Update();
	void printInfo();

};