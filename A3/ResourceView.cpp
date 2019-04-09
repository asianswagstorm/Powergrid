#include "ResourceView.h"
#include "IOFile.h"
#include <iostream>
#include <fstream>
using namespace std;
ResourceView::ResourceView() {}

ResourceView::~ResourceView() {}

ResourceView::ResourceView(View * view)  {
	subject = view->subject;
	subject->removeObserver(view);
	subject->registerObserver(this);
	setType(view->getType() + "-Resource-");
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

	vector<Player*> players = subject->player_vector;;
		//IOFile::loadPlayer();
	ResourceMarket * resourceMarket = IOFile::loadResourceMarket();

	for (unsigned int i = 0; i < players.size(); i++) {
		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Coal") << " Coal." << std::endl; //print to console
		std::cout << "The Market only has " << resourceMarket->getMarketQuantity("Coal") << " Coal." << std::endl <<std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Oil") << " Oil." << std::endl; //print to console
		std::cout << "The Market only has " << resourceMarket->getMarketQuantity("Oil") << " Oil." << std::endl << std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Garbage") << " Garbage." << std::endl; //print to console
		std::cout << "The Market only has " << resourceMarket->getMarketQuantity("Garbage") << " Garbage." << std::endl << std::endl;//print to console

		std::cout << players[i]->getName() << " has " << players[i]->getResourceQuantity("Uranium") << " Uranium." << std::endl; //print to console
		std::cout << "The Market only has " << resourceMarket->getMarketQuantity("Uranium") << " Uranium." << std::endl << std::endl;//print to console
 
		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Coal") << " Coal." << std::endl; //print to game_stats
		output << "The Market only has " << resourceMarket->getMarketQuantity("Coal") << " Coal." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Oil") << " Oil." << std::endl; //print to game_stats
		output << "The Market only has " << resourceMarket->getMarketQuantity("Oil") << " Oil." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Garbage") << " Garbage." << std::endl; //print to game_stats
		output << "The Market only has " << resourceMarket->getMarketQuantity("Garbage") << " Garbage." << std::endl << std::endl;//print to game_stats

		output << players[i]->getName() << " has " << players[i]->getResourceQuantity("Uranium") << " Uranium." << std::endl; //print to game_stats
		output << "The Market only has " << resourceMarket->getMarketQuantity("Uranium") << " Uranium." << std::endl << std::endl;//print to game_stats
	}
	std::cout << std::endl;
	output << std::endl;

}