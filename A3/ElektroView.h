#pragma once
#include "View.h"
class ElektroView : public View {
public:
	ElektroView();
	~ElektroView();
	ElektroView(View * view);
	ElektroView(Game * game);

	void Update(); //abstract Update
	void printInfo(); //abstract print

};