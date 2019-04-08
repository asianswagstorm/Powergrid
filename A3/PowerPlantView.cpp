#include "PowerPlantView.h"
#include "IOFile.h"
#include <iostream>
#include <fstream>
using namespace std;

PowerPlantView::PowerPlantView() {}
PowerPlantView::~PowerPlantView() {}

void PowerPlantView::Update() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "PowerPlant Info" << std::endl << std::endl;
	this->printInfo();
}
void PowerPlantView::printInfo() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);

	vector<Player*> players = IOFile::loadPlayer();
	vector<PowerPlant> * powerplants = IOFile::loadPowerplants(players); //all powerplants
	vector<PowerPlant> * powerplantCardsShowned = new vector<PowerPlant>();
	vector<PowerPlant> * powerplantActualMarket = new vector<PowerPlant>();

	for (unsigned int i = 0; i < players.size(); i++) {
		std::cout << players[i]->getName() << " has " << players[i]->Player::getPowerPlants()->size() << " powerplants " << std::endl; 	 //print to console
		output << players[i]->getName() << " has " << players[i]->Player::getPowerPlants()->size() << " powerplants " << std::endl;// print to game_stats
		
		std::cout << std::endl; 	 //print to console
		output << std::endl; // print to game_stats
	}
	std::cout << std::endl;
	output << std::endl;
	std::cout << std::endl << "---------------  Actual Market  ------------" << std::endl;

	for (int i = 0; i < 8; i++) { 
		powerplantCardsShowned->push_back((*powerplants)[i]);
		if (i < 4)
			powerplantActualMarket->push_back((*powerplantCardsShowned)[i]);

		if (i == 4)
			std::cout << std::endl << "---------------  Future Market  ------------" << std::endl;

		(*powerplantCardsShowned)[i].printPowerPlantSummary();

	}

}