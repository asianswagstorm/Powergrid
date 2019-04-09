#include "BasicView.h"
#include <string>
#include <fstream>
BasicView::BasicView() {}
//attach observer to subject by calling super construtor.
BasicView::BasicView(Game * game) : View(game) {}
BasicView::~BasicView(){}

void BasicView::Update() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "Basic Info" << std::endl << std::endl;
	this->printInfo();
}
void BasicView::printInfo() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	vector<Player*> player_vector = subject->player_vector;

	cout << "hi" <<std::endl << std::endl;
	output << "hi" << std::endl << std::endl;

}