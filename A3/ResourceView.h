#pragma once
#include "ViewDecorator.h"
class ResourceView : public ViewDecorator {
public:
	ResourceView();
	~ResourceView();
	ResourceView(View * decoratedView);
	void Update();
	void printInfo();

};