#include "HouseView.h"
#include "IOFile.h"
#include <iostream>
#include <fstream>
using namespace std;
HouseView::HouseView() {}
HouseView::~HouseView() {}
HouseView::HouseView(View * view)  {
	subject = view->subject;
	subject->removeObserver(view);
	subject->registerObserver(this);
	setType(view->getType() + "-House-");
}

void HouseView::Update() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "House Info" << std::endl << std::endl;
	this->printInfo();
}
void HouseView::printInfo() {
	vector<Player*> player_vector = subject->player_vector;
	
	vector<House> house_vector = subject->house_vector;
		//IOFile::loadPlayerHouse(player_vector);

	for (unsigned int i = 0; i < player_vector.size(); i++) {
		//Map theMap = Map(player_vector[i]->Player::getAreaColor());
		Map::instance()->createMap(player_vector[i]->Player::getAreaColor());
		for (unsigned int j = 0; j < player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector().size(); j++) {
			std::cout << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() << " (" << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getLocation() << ") " << ",";
			
		}//end for
	} //end for
}