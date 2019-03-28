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


int main() {

	/*
	1) the game valid board map can be loaded and its verified  and invalid map(s) are rejected without the program crashing;
	2) the right number of players is created, and the right game pieces created.);
		*/
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
	game->Game::buyPowerPlant();
	game->Game::buyMaterial();
	game->Game::buildHouse();
	game->Game::bureaucracy();

	system("pause");
	return 0;
}