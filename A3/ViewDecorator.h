#pragma once
#include "View.h"

//Decorator Design Pattern for the view
class ViewDecorator : public View {

public:
	ViewDecorator();
	ViewDecorator(View * decoratedView);
	virtual ~ViewDecorator();

protected:
	View * decoratedView;
};