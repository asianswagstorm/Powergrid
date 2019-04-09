#pragma once
#include "ViewType.h"
class ElektroView : public ViewType {
public:
	ElektroView();
	~ElektroView();
	ElektroView(ViewType * type);

	void Update();
	void printInfo();

};