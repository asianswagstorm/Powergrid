#include "AllView.h"
#include <string>
#include <fstream>
AllView::AllView() {}
AllView::AllView(Game * game) : Statistics(game) {}
AllView::~AllView(){}

void AllView::Update() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "General Info" << std::endl << std::endl;
	this->printInfo();
}
void AllView::printInfo() {
	ofstream output;
	output.open("gamelog.txt", ios::out | ios::app);


}