#pragma once
#include "ViewDecorator.h"
class ElektroView : public ViewDecorator {
public:
	ElektroView();
	~ElektroView();
	ElektroView(View * decoratedView);

	void Update(); //abstract Update
	void printInfo(); //abstract print

};