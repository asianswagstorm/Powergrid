#pragma once
#include "View.h"
class ResourceView : public View {
public:
	ResourceView();
	~ResourceView();
	ResourceView(View * view);
	void Update();
	void printInfo();

};