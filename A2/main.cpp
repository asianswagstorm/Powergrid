#include <iostream>
#include <vector>
#include "PowerPlant.h"
#include <cstdlib>
#include <algorithm> // std::random_shuffle
#include <ctime> // std::time()
#include "SummaryCard.h"
#include "Map.h"
#include "Area.h"
#include "IOFile.h"
#include "mapreader.h"
#include "Player.h"

#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <list>

int main() {


	//1) Select a map (a map is separated into 6 areas, each with 7 cities) from a list of file(s) as stored in a directory.
	//europe and us map pick which map. 

	/*
	map loader to load the selected and appropriate map file.
	the deck of the summary cards,

	LOAD
	DONE? power plant cards,

	the houses objects,
	resources tokens,
	the money(elektro),
	and the “step 3” card. ?? What's this???

	1) the game valid board map can be loaded and its verified  and invalid map(s) are rejected without the program crashing;
	2) the right number of players is created, and the right game pieces created.);

		*/
	int numPlayers;
	string player_name, color, response;
	bool isValidColorInput = false;
	std::vector<Player*> player_vector;
	std::vector<SummaryCard*> summary_card_vector;
	vector<int> areas; //2-3 playes 3 areas , 4 players  4 areas, 5-6 players 5 areas  

	//NEW (new) OR LOAD GAME. 
	std::cout << "Write \"new\" for a NEW GAME." << std::endl << std::endl; 
	std::cout << "Press any key to LOAD a game." << std::endl; 
	cin >> response;

	if (response != "new") {
		//Load map
		mapreader map;
		/*
		Game loadGame ("player.txt", "area.txt", "map.txt", "powerplant.txt", "nbPlayerAndTurn.txt")
		//turnorder which player goes first (player with less cities)
		*/
		map.readMap(); //read the edges too
		return 0;
	}
	else {
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
				if (color == "purple" || color == "blue" || color == "red" || color == "yellow" || color == "brown" || color == "brown")
				{
					//if color not in 
					if (areas.size() != 0) {
						for (int j = 0; j < areas.size(); j++) {
							if (areas[j] == Area::getAreaNumber(color)) {
								std::cout << "Area already chosen , Please pick another location:" << std::endl;
							}
							else {
								isValidColorInput = true;
								break;
							}
						}
					}
					else {
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

			//create player
			Player* player = new Player(player_name, color);
			std::cout << std::endl << "Player Created! Here are " << player_name << "'s current stats:" << std::endl;

			player->printPlayerInfo();
			player_vector.push_back(player);

			//Overview / summary card
			SummaryCard *sc = new SummaryCard();
			summary_card_vector.push_back(sc);
			std::cout << std::string("===========Here is your summary card=============") << std::endl << std::endl;
			sc->SummaryCardInfo();

			isValidColorInput = false;
		}

		if (Area::areAdjacent(areas) == false) {
			std::cout << "Error, areas are not adjacent! " << std::endl;
			system("pause");
			return 1;
		}

		else {

			//Powerplant Cards 
			PowerPlant::pool(); // should show only 8, shuffled 

			Area::setGameAreas(areas);
			//create map
			Map theMap = Map();
			//Save map to map.txt
			IOFile::saveMap(); //load map should read the edges too
			


		}


	}
	system("pause");
	return 0;
}