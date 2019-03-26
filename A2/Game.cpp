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
#include "PowerPlantHelper.h"
#include "Map.h"
#include "mapreader.h"
#include "IOFile.h"
#include "SummaryCard.h"

Game::Game() {
	round = 0; //default contructor, no game so no round 
}
//need to save the round number for load
Game::Game(std::vector<Player*> player_vector, Map *map) {
	round = 1; //player's first game round , set round as 2 to test load game
	this->player_vector = player_vector;
}
Game::~Game() { //destructor
}

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
	int numPlayers = 0;
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

//TODO::: READ PLAYER FILE, check HOUSES. if tie, check Powerplant

/*During this phase, the new player order is determined.The first player is the player with the most cities in his network(first house on the scoring track).If two or more players
are tied for the most cities, the first player is the player among them with the largest - numbered power plant.Place this player‘s house in the first position in the player order
area.Determine the remaining player positions using the same rules.*/
void Game::determinePlayerOrder() {

	switch (Game::getRound()) {
	case(1): {//if the first round every player have 0 houses, so game order is random. //Problem with LOAD
		std::cout << endl << "This is the first round, all players have equal amount of houses and powerplants, Order is Random" << endl;
		std::random_shuffle(this->player_vector.begin(), this->player_vector.end()); // from algorithm
		IOFile::savePlayerOrder(player_vector);
		break;

	}
	default: {
		std::cout << "Player order is decided on the player with the highest controlled cities (Houses owned)" << endl <<
			"If a tie exists, then order is decided based on player with highest owned powerplants. " << endl;
		int nextPlayer = 0, i = 0, firstPlayer;
		firstPlayer = Game::getFirstPlayer(this->player_vector, i);
		for (Player* p : this->player_vector) {
			nextPlayer = Game::getFirstPlayer(this->player_vector, i);
			swapPlayers(*player_vector[i], *player_vector[nextPlayer]);
			i++;
		}
		IOFile::savePlayerOrder(player_vector);
		std::cout << endl << "------------------PLAYER ORDER ----------------" << endl;

		for (Player* player : this->player_vector) {
			std::cout << player->getName() << ", " << player->getHouseCounter() << " Houses, " << player->getnumOfPowerPlants() << " PowerPlants. " << std::endl;
		}
		
		break;
	}
	}
}

int Game::getFirstPlayer(std::vector<Player*> player_vector, int i) {
	int max = i;
	int maxHouse = player_vector[i]->Player::getHouse()->HouseHelper::getHouse();
	int maxPowerPlant = player_vector[i]->Player::getnumOfPowerPlants(); 
	//Player::getPowerPlants()->size() 
	
	for (unsigned int j = i+1; j < player_vector.size(); j++) {
		if (player_vector[j]->Player::getHouse()->HouseHelper::getHouse() > maxHouse) {

			maxHouse = player_vector[j]->Player::getHouse()->HouseHelper::getHouse();
			max = j;
		}

		else if (player_vector[j]->Player::getHouse()->HouseHelper::getHouse() == maxHouse) {
			if (player_vector[j]->getnumOfPowerPlants() > maxPowerPlant) {
				maxPowerPlant = player_vector[j]->getnumOfPowerPlants();
				max = (j);

			}
		}
	}
	
	return max;
}

void Game::swapPlayers(Player& player1, Player& player2) {
	Player temp;
	temp = player1;
	player1 = player2;
	player2 = temp;
}

void Game::buyPowerPlant() {
	int AuctionWinner=-1, playerBid = -1 , k = 0, playersWithAuction = -1;
	string response = "" ;

	//reset the auction status
	for (unsigned int j = 0; j < this->player_vector.size(); j++) {
		player_vector[j]->resetAuction();
	}

	for (unsigned int i = 0; i < this->player_vector.size(); i++) { //loop every player to let them buy powerplants

		if (player_vector[i]->getPass() == true) { // if already bought powerplant, skip player.
			player_vector[i]->auction(); //set auction = true
			continue; //gets out of the loop
		}

		powerplanthelper->PowerPlantHelper::printPPMarket();

		std::cout << std::endl << "PHASE 2 POWERPLANT AUCTIONING" << std::endl ;
		std::cout << std::endl << player_vector[i]->getName() << " starts the bid " << std::endl << std::endl;
	
		if(Game::getRound() > 1){ // first round player must buy powerplant
		while (response != "yes" && response != "no") {
			std::cout << "Do you want to auction on a powerplants (yes/no): ";
			cin >> response; std::cout << endl;
		}

		if (response == "no") {
			cout << player_vector[i]->getName() << " has passed on auctioning a power plant." << endl;
			player_vector[i]->pass();
			continue;
		}
		}

		while(powerplanthelper->PowerPlantHelper::isPPActual(playerBid) == false || player_vector[i]->getElectro() < playerBid)
			{ //if invalid bid (inssuficient fund or powerplant not in actual market

		std::cout << player_vector[i]->getName() << " currently has " << player_vector[i]->getElectro() << " elektros " << std::endl;
		std::cout << "Enter a bid less than equal to max powerplant card number in actual market." << std::endl << "(This is the minimum bid in Electros to purchase the powerplant) : " << endl;

		cin >> playerBid;
	
	
		//check if in actual market.
		if (powerplanthelper->PowerPlantHelper::isPPActual(playerBid) == false) {
			cout << endl << "!!!! This powerplant card is not in the Actual Market, INVALID BID" << endl << endl;
		}else if (player_vector[i]->getElectro() < playerBid) {
			cout << endl << "!!!! Insufficient funds, PowerPlant: " << playerBid << " costs " << playerBid << "Elektros" << endl;
			std::cout << "You only have "<< player_vector[i]->getElectro() << " Elektros " << endl;
		}
	
			}

		int powerplantNum = playerBid;
		//if True 

		std::vector<Player*> player_with_auction;
		//check if player has auction
		
		for (Player* players : player_vector) {
			if (players->Player::getAuction() == true) {
				player_with_auction.push_back(player_vector[k]);
				k++;
			}
		}

		playersWithAuction = player_with_auction.size();

		
		std::cout << player_vector[AuctionWinner]->getName() << " won the auction for powerplant: " << powerplantNum << endl;
		player_vector[AuctionWinner]->pass();
		//player_vector[AuctionWinner]->addPowerPlant(powerplanthelper->  getAndRemoveSpecificPowerplant(intialPlantValue));
		player_vector[AuctionWinner]->removeElectro(powerplantNum);
		
	}//main for loop done

}

