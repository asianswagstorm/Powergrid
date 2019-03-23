#include <iostream>
#include <algorithm>
#include <ctime> // std::time()
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>

#include "Game.h"
#include "PowerPlant.h"
#include "Map.h"
#include "mapreader.h"
#include "IOFile.h"
#include "SummaryCard.h"

Game::Game() {
	round = 0; //default contructor, no game so no round 
}
//need to save the round number for load
Game::Game(std::vector<Player*> player_vector, Map *map) {
	round = 1; //player's first game round 
	this->player_vector = player_vector;
}
Game::~Game() { //destructor
}

void Game::buyPowerPlant() {}

void Game::loadGame(int numPlayers) {
	//Load map
	mapreader map;
	string mapFileName;
	std::cout << "Enter map file name not including .txt" << std::endl;
	cin >> mapFileName;
	/*
	Game loadGame ("powerplant.txt", "numPlayersAndTurn.txt")
	//turnorder which player goes first (player with less cities)
	*/
	map.readMap(mapFileName);
	player_vector = IOFile::loadPlayer();
	numPlayers = player_vector.size();

	for (int i = 0; i < numPlayers; i++) {
		SummaryCard *sc = new SummaryCard();
		std::cout << endl << "===========Here is player" << i + 1 << "'s summary card=============" << std::endl << std::endl;
		sc->SummaryCardInfo();
	}

	powerplanthelper = new PowerPlantHelper(); // should show only 8 // Also should keep track of discarded cards or cards already in game. 
}


void Game::setUpGame() {
	int numPlayers = 0, houseIndex;
	string player_name, color;
	std::vector<SummaryCard*> summary_card_vector;
	vector<int> areas; //2-3 playes 3 areas , 4 players  4 areas, 5-6 players 5 areas  
	bool isValidColorInput = false;
	std::cout << "\nNew Game Starting..." << std::endl;

	do {
		std::cout << "How many players would like to play the game? (2-6): " << std::endl;
		cin >> numPlayers;
	} while (numPlayers < 2 || numPlayers > 6);

	for (int i = 0; i < numPlayers; i++) {

		std::cout << "Player " << i + 1 << " name: " << std::endl;
		cin >> player_name;
		std::cout << "Player " << i + 1 << " location color: " << std::endl;

		while (isValidColorInput == false) { //Handling for a valid area color input
			cin >> color;
			if (color == "purple" || color == "blue" || color == "red" || color == "yellow" || color == "brown" || color == "green")
			{
				//if color not in 
				if (areas.size() != 0) {
					for (unsigned int j = 0; j < areas.size(); j++) {
						if (areas[j] == Area::getAreaNumber(color)) {
							std::cout << "Area already chosen , Please pick another location:" << std::endl;
						}
						else {
							Map theMap = Map(color);
							isValidColorInput = true;
							break;
						}
					}
				}
				else {
					Map theMap = Map(color);
					isValidColorInput = true;
					break;
				}


			}
			else {
				std::cout << "Invalid Color Input, Please try again:" << std::endl;
			}
		}

		//handle 1 area per player

		areas.push_back(Area::getAreaNumber(color));

		HouseHelper* hh = new HouseHelper();
		/* Build House
		//addhouse show available
		std::cout << "Pick a city index to place your initial house: " << std::endl;
		cin >> houseIndex;
		House aHouse = House(houseIndex, Map::getCityName(houseIndex), color);
		hh->addHouse(aHouse);
		std::cout << std::endl << "House add in: "  << hh->getHouseVector()[0].getLocation() << std::endl;
		*/

		//create player
		Player* player = new Player(player_name, color, hh); //need to save player into file to be loaded
		std::cout << std::endl << "Player Created! Here are " << player_name << "'s current stats:" << std::endl;

		player->printPlayerInfo();
		this->player_vector.push_back(player);

		//Overview / summary card
		SummaryCard *sc = new SummaryCard();
		summary_card_vector.push_back(sc);
		std::cout << std::string("===========Here is your summary card=============") << std::endl << std::endl;
		sc->SummaryCardInfo();

		isValidColorInput = false;
	}

	if (Area::areAdjacent(areas) == false) {
		std::cout << "Error, areas are not adjacent! " << std::endl;
	}

	else {

		//Powerplant Cards 
		powerplanthelper = new PowerPlantHelper();

		Area::setGameAreas(areas);
		//save players 
		IOFile::savePlayer(player_vector);
		//create map
		//Save map to map.txt
		IOFile::saveMap(); //load map should read the edges too
	
	}
}

void Game::setRound(int round) {
	this->round = round;
}
int Game::getRound() const {
	return round;
}

/*During this phase, the new player order is determined.The first player is the player with the most cities in his network(first house on the scoring track).If two or more players
are tied for the most cities, the first player is the player among them with the largest - numbered power plant.Place this player‘s house in the first position in the player order
area.Determine the remaining player positions using the same rules.*/
void Game::determinePlayerOrder() {

	switch (round)  {
	case(1): {//if the first round every player have 0 houses, so game order is random.
		std::cout << endl<<"This is the first round, all players have equal amount of houses and powerplants, Order is Random" << endl;
		std::random_shuffle(player_vector.begin(), player_vector.end()); // from algorithm
		break;

	}
	default: {
		std::cout << "Player order is decided on the player with the highest controlled cities (Houses owned)" << endl <<
			"If a tie exists, then order is decided based on player with highest owned powerplants. " << endl;
		int max = 0;
		//
		for (int i = 0; player_vector.size(); i++) {

		}


	}


	}

}

int Game::getFirstPlayer(std::vector<Player*> player_vector) {
	int house = player_vector[0]->getHouse()->getHouse(); //player->househelper->int
	//int powerplant = player_vector[0];
	int max = 0;
	return 0;
}