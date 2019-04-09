#include "ResourceView.h"
#include "IOFile.h"
#include <iostream>
#include <fstream>
using namespace std;
ResourceView::ResourceView() {}

ResourceView::~ResourceView() {}

ResourceView::ResourceView(Statistics * stats) {
	subject = stats->subject;
	subject->removeObserver(stats);
	subject->registerObserver(this);
	setType("Resource");
}
void ResourceView::Update() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "Resource Info" << std::endl << std::endl;
	this->printInfo();

}
void ResourceView::printInfo() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);

	vector<Player*> players = IOFile::loadPlayer();
	ResourceMarket * market = IOFile::loadResourceMarket();

	for (unsigned int i = 0; i < players.size(); i++) {
		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Coal") << " Coal." << std::endl; //print to console
		std::cout << "The Market only has " << market->getMarketQuantity("Coal") << " Coal." << std::endl <<std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Oil") << " Oil." << std::endl; //print to console
		std::cout << "The Market only has " << market->getMarketQuantity("Oil") << " Oil." << std::endl << std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Garbage") << " Garbage." << std::endl; //print to console
		std::cout << "The Market only has " << market->getMarketQuantity("Garbage") << " Garbage." << std::endl << std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Uranium") << " Uranium." << std::endl; //print to console
		std::cout << "The Market only has " << market->getMarketQuantity("Uranium") << " Uranium." << std::endl << std::endl;//print to console
 
		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Coal") << " Coal." << std::endl; //print to game_stats
		output << "The Market only has " << market->getMarketQuantity("Coal") << " Coal." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Oil") << " Oil." << std::endl; //print to game_stats
		output << "The Market only has " << market->getMarketQuantity("Oil") << " Oil." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Garbage") << " Garbage." << std::endl; //print to game_stats
		output << "The Market only has " << market->getMarketQuantity("Garbage") << " Garbage." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Uranium") << " Uranium." << std::endl; //print to game_stats
		output << "The Market only has " << market->getMarketQuantity("Uranium") << " Uranium." << std::endl << std::endl;//print to game_stats
	}
	std::cout << std::endl;
	output << std::endl;

}