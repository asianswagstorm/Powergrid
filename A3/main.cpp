#include <cstdlib>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <list>

#include "Game.h"
#include "Map.h"
#include "View.h"
#include "ElektroView.h"
#include "HouseView.h"
#include "PowerPlantView.h"
#include "ResourceView.h"

int main() {
	ofstream output;
	output.open("game_statistics.txt");
	int numPlayers=0;
	std::vector<Player*> player_vector;
	string response;
	Game *game = new Game(player_vector, Map::instance());
	
	//NEW (new) OR LOAD GAME. 
	std::cout << "Write \"new\" for a NEW GAME." << std::endl << std::endl; 
	std::cout << "Press any key to LOAD a game." << std::endl; 
	cin >> response;

	if (response != "new") {
		game = game->Game::loadGame(numPlayers);
		game->setRound(2); // temporary
	}
	else {
		//game->Game::setUpGame();
		game = game->Game::setUpGame();
		//Map::testMap(Map::instance()); //(OPTIONAL TO TEST IF CONNECTED GRAPH) 
	}
	std::cout << std::endl << "stats" << std::endl << std::endl;
	//nothing
	
	View * aView = new ElektroView(game);
	aView->printInfo();
	aView = new ResourceView(aView);
	aView->printInfo();
	aView = new PowerPlantView(aView);
	aView->printInfo();
	aView = new HouseView(aView);
	aView->printInfo();

	//int maxRound = 4;
	//int startRound =1;
	//while(startRound < maxRound){
		 game->Game::determinePlayerOrder(); //reorganizes the player vector , first player in front of vector.
		 std::cout << endl;
		 game->Game::buyPowerPlant();
		 game->Game::buyResources(); //done 
		 game->Game::buildHouse();
	     game->Game::bureaucracy(); 
		
		//startRound++;
	//}
	system("pause");
	return EXIT_SUCCESS;
}