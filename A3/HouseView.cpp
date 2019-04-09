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
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);

	vector<Player*> player_vector = subject->player_vector;
	vector<House> house_vector = IOFile::loadPlayerHouse(player_vector);

	std::cout << "---------------House View-----------------" << std::endl << std::endl;
	output << "---------------House View-----------------" << std::endl << std::endl;

	for (unsigned int i = 0; i < player_vector.size(); i++) {
		//Map theMap = Map(player_vector[i]->Player::getAreaColor());
		Map::instance()->createMap(player_vector[i]->Player::getAreaColor());
		std::cout << player_vector[i]->getName() << "'s houses: " << std::endl;
		output << player_vector[i]->getName() << "'s houses: " << std::endl;
		for (unsigned int j = 0; j < player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector().size(); j++) {
			if (player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getisPowered() == true) {
				std::cout << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() << " (" << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getLocation() << ") POWERED" << ",";
				output << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() << " (" << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getLocation() << ") POWERED" << ",";
			}
			else{
			std::cout << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() << " (" << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getLocation() << ") " << ",";
			output << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() << " (" << player_vector[i]->Player::getHouse()->HouseHelper::getHouseVector()[j].getLocation() << ") " << ",";
			}
		}//end for
		std::cout << std::endl;
		output<< std::endl;
	} //end for
}