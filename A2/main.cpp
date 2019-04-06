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

int main() {

	int numPlayers=0;
	std::vector<Player*> player_vector;
	Map * map = new Map;
	string response;
	Game * game = new Game(player_vector, map);
	
	//NEW (new) OR LOAD GAME. 
	std::cout << "Write \"new\" for a NEW GAME." << std::endl << std::endl; 
	std::cout << "Press any key to LOAD a game." << std::endl; 
	cin >> response;

	if (response != "new") {
		game->setRound(2); // temporary
		game->Game::loadGame(numPlayers);
	}
	else {
		game->Game::setUpGame();
		//Map::testMap(map); //(OPTIONAL TO TEST IF CONNECTED GRAPH) 
	}

	game->Game::determinePlayerOrder(); //reorganizes the player vector , first player in front of vector.
	std::cout << endl;
	//game->Game::buyPowerPlant();
	  game->Game::buyResources(); //done //still need to save to file
	//game->Game::buildHouse();
	//game->Game::bureaucracy(); //redo

	system("pause");
	return EXIT_SUCCESS;
}