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
#include "player.h"
#include "resource.h"

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

	for (unsigned int j = i + 1; j < player_vector.size(); j++) {
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

Player * Game::getNextPlayer(Player & p) {

	if (this->player_vector.size() == 2) {

		if (&p == &*player_vector[0]) {
			return player_vector[1];
		}
	}

	if (this->player_vector.size() == 3) {

		if (&p == &*player_vector[1]) {
			return player_vector[2];
		}
		if (&p == &*player_vector[0]) {
			return player_vector[1];
		}
	}

	if (this->player_vector.size() == 4) {

		if (&p == &*player_vector[2]) {
			return player_vector[3];
		}

		if (&p == &*player_vector[1]) {
			return player_vector[2];
		}
		if (&p == &*player_vector[0]) {
			return player_vector[1];
		}
	}

	if (this->player_vector.size() == 5) {

		if (&p == &*player_vector[3]) {
			return player_vector[4];
		}

		if (&p == &*player_vector[2]) {
			return player_vector[3];
		}

		if (&p == &*player_vector[1]) {
			return player_vector[2];
		}
		if (&p == &*player_vector[0]) {
			return player_vector[1];
		}
	}

	if (this->player_vector.size() == 6) {

		if (&p == &*player_vector[4]) {
			return player_vector[5];
		}

		if (&p == &*player_vector[3]) {
			return player_vector[4];
		}

		if (&p == &*player_vector[2]) {
			return player_vector[3];
		}

		if (&p == &*player_vector[1]) {
			return player_vector[2];
		}
		if (&p == &*player_vector[0]) {
			return player_vector[1];
		}
	}

	return player_vector[0];
}

void Game::buyPowerPlant() {
	int AuctionWinner, playersWithAuction, auctionSize = -1, auction_bid = -2, temp = 0;
	string response; //response= would you like to but a plant? //used to reset the response when a player responds
	string bid_response = ""; // do you want to join the auction war for a powerplant
	std::vector<Player*> player_with_Auction_vector;
	int numPlayers = this->player_vector.size();
	//reset the auction status
	for (unsigned int j = 0; j < numPlayers; j++) {
		player_vector[j]->resetAuction();
	}

	for (unsigned int i = 0; i < numPlayers; i++) { //loop every player to let them buy powerplants
		Player * p = player_vector[i];
		bool isInActual = false;
		bool canAfford = false;

		auctionSize = (int)i; //players with auction
		int init_playerBid;

		//reset auction again.
		for (unsigned int q = 0; q < numPlayers; q++) {
			player_vector[q]->resetAuction();

		}

		// if already bought powerplant, skip player.
		if (player_vector[i]->getPass() == true) {
			player_vector[i]->auction(); //set auction = true
			player_with_Auction_vector.push_back(player_vector[i]);
			continue; //gets out of the loop
		}
		std::cout << std::endl << "PHASE 2 POWERPLANT AUCTIONING" << std::endl;
		powerplanthelper->PowerPlantHelper::printPPMarket();



		if (i == 0)
			std::cout << std::endl << player_vector[i]->getName() << " is the first person to start the bid according to the player order rules. " << std::endl << std::endl;

		else {
			//check if previous player has passed on bid
			if (player_vector[i - 1]->getPass() == true) { //passed up on starting a bid. 
				auctionSize--; //skip the player
			}
			std::cout << std::endl << player_vector[i]->getName() << "'s turn. " << std::endl;
			std::cout << "To start the bid " << std::endl;
		}

		response = "";
		if (Game::getRound() >= 1) { // first round player must buy powerplant , I set round = 2 for testing in main. 
			while (response != "yes" && response != "no") {
				std::cout << player_vector[i]->getName() << ", do you want to auction on a powerplant (yes/no): ";
				cin >> response; std::cout << endl;
			}

			if (response == "no") {
				cout << player_vector[i]->getName() << " has passed on auctioning a power plant." << endl;
				player_vector[i]->pass(); //passing the oppurtunity to buy a powerplant
				continue;
			}// end no
		}//end if round
		if (response == "yes") {
			//player_vector[i]->setPass(false); //Didnt pass on buying a powerplant
			while (isInActual == false || canAfford == false)
			{ //if invalid bid (inssuficient fund or powerplant not in actual market
				std::cout << player_vector[i]->getName() << " currently has " << player_vector[i]->getElectro() << " elektros " << std::endl;
				std::cout << "Enter a bid less than equal to max powerplant card number in actual market." << std::endl << "(This is the minimum bid in Electros to purchase the powerplant) : " << endl;

				cin >> init_playerBid;

				isInActual = powerplanthelper->PowerPlantHelper::isPPActual(init_playerBid);
				canAfford = (player_vector[i]->getElectro() > init_playerBid);

				//check if in actual market.
				if (isInActual == false) {
					cout << endl << "!!!! This powerplant card is not in the Actual Market, INVALID BID" << endl << endl;
				}
				else if (canAfford == false) {
					cout << endl << "!!!! Insufficient funds, PowerPlant: " << init_playerBid << " costs " << init_playerBid << " Elektros" << endl;
					std::cout << "You only have " << player_vector[i]->getElectro() << " Elektros " << std::endl << std::endl;
				}
				std::cout << "Correct Input, card " << init_playerBid << " is in actual market." << std::endl << std::endl;
				player_vector[i]->auction();
			}//end while
		}//end response yes
	//auction while  
		while (auctionSize != numPlayers) { // while not end of player round

			cout << endl << " Numb Players : " << numPlayers << endl << endl;
			cout << " players with auction: " << player_with_Auction_vector.size() << endl << endl; //2 ?
			cout << " auction size: " << auctionSize << endl;

			int playersWithAuction = player_with_Auction_vector.size();

			if (auctionSize == numPlayers - 1 || numPlayers - playersWithAuction == 1) { // if last player or last player has no auction

				int k = 0;
				for (int j = 0; j < numPlayers; j++) {

					if (player_vector[j]->getAuction() == false) {
						AuctionWinner = k;
						cout << endl << "Winner is: " << AuctionWinner << endl;
					}

					k++;

				}
				break;
			}

			std::cout << std::endl << "------------ Starting Auction -----------" << std::endl << std::endl;

			Player * p = Game::getNextPlayer(*player_vector[i]); //get next player to start an auction

			while (p->getAuction() == true) {
				p = getNextPlayer(*p);
			}

			if (p->getElectro() < init_playerBid) {
				std::cout << p->getName() << "Insufficient funds to bid" << std::endl;
				auctionSize++;
				p->auction();
				continue;
			}
			if (temp == 0) {
				temp = init_playerBid;
			}

			std::cout << "The Current Bid for powerplant : #" << temp << " is " << init_playerBid << " Elektros" << endl;
			std::cout << p->getName() << " Would you wish to bid on this powerplant? Type yes or no " << endl;
			cin >> bid_response;

			if (bid_response == "yes") {//auction is true
				std::cout << "Please enter the amount you want to bid for powerplant: " << temp << std::endl;
				cin >> auction_bid;

				bool lowBid = auction_bid <= init_playerBid;
				bool cantAfford = p->getElectro() < init_playerBid;

				if (lowBid) { //can no longer bid
					cout << std::endl << "This bid is too low, you lose the chance to buy a powerplant this round." << std::endl;
					//p->setAuction(false); // set auction to be false
					p->auction();
					player_with_Auction_vector.push_back(p);
					auctionSize++;

				}
				else if (cantAfford) { //can no longer bid
					cout << std::endl << "You do not have enough electro to buy this powerplant." << std::endl;
					//p->setAuction(false); // set auction to be true
					p->auction();
					player_with_Auction_vector.push_back(p);
					auctionSize++;

				}

				if (lowBid == false && cantAfford == false) { //If won auction

					init_playerBid = auction_bid;

					std::cout << "The bid for plant: " << temp << " changed to: " << init_playerBid << std::endl << std::endl;
					//p->setAuction(false); // set auction to be false used to determine auction winner
					p->auction();
					player_with_Auction_vector.push_back(p);
					auctionSize++;
				}
				p->pass();
			}//end yes bid_response

			if (bid_response == "no") { //Don't want to join the bidding war, should go to next.
				temp = temp;
				std::cout << p->getName() << " has passed on joining the auction for powerplant:" << init_playerBid << std::endl;
				p->auction(); // set auction to be true
				player_with_Auction_vector.push_back(p);
				auctionSize++;
			}

		}//end auction while 	

		int powerplantNum = temp;
		//Errors
		//std::cout << player_vector[AuctionWinner]->getName() << " won the auction for powerplant: " << powerplantNum << std::endl << std::endl;
		//player_vector[AuctionWinner]->setAuction(false);
		//player_vector[AuctionWinner]->pass();
		//player_vector[AuctionWinner]->setnumOfPowerPlants(player_vector[AuctionWinner]->getnumOfPowerPlants() + 1);
		//player_vector[AuctionWinner]->addPowerPlant(powerplanthelper->removePowerPlant(powerplantNum));
		//player_vector[AuctionWinner]->removeElectro(powerplantNum);

	}//main for loop done
	std::cout << std::endl << "-------------Player Stats Updated------------------" << std::endl << std::endl;
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		player_vector[i]->printPlayerInfo();
	}

}

void Game::bureaucracy() {
	int choice;

	cout << "*****************************************************************" << endl;
	cout << " PART 5: BUREAUCRACY" << endl;
	cout << "*****************************************************************" << endl;

	string powerDecision;
	vector<int> numberCitiesPoweredAtEnd;

	reverse(player_vector.begin(), player_vector.end());
	for (Player* player : player_vector) {

		int poweredPlants[3] = { -1,-1,-1 }; //Initial status (no powered plants)
		/*Money received depends on the number of powered houses.
		<---->If no house powered ---> the automatically 10 elektro.
		- Giving them the ability to decide how many houses they want to power based on their resources.*/
		cout << "**********************************************************************************************************************" << endl;
		cout << "Player " << player->getAreaColor() << " has " << player->getHouse()->getHouse() << " houses." << endl;
		cout << "Attention: You can only power cities that you own, any powering except that will be a loss of resources." << endl;
		cout << "**********************************************************************************************************************" << endl;
		cout << "Do you want to power any Cities?";
		cout << "(yes or no)";
		cin >> powerDecision; cout << endl;


		//If yes, player will power cities
		if (powerDecision == "yes") {
			choice = -1;
			int numberCitiesPowered = 0;

			//case 1: no houses to power---> 10 elektros will be offered to the player
			if (player->getHouseCounter() == 0) {
				choice = 0;
				cout << "You have no cities to power!" << endl;
				cout << "You are offered 10 Elektros" << endl;
				player->printPlayerInfo();
			}

			while (choice != 0) {
				player->printPlayerInfo();
				//Request to enter plant--> if no break
				cout << "What plant do you wish to power: ";
				cout << "(If you wish to exit enter 0)";
				cin >> choice;
				cout << endl;

				for (int i = 0; i <= 2; i++) {
					if (poweredPlants[i] == -1) {
						poweredPlants[i] = choice;

						player->powerACity(choice);
						numberCitiesPowered += player->getnumOfPowerPlants(choice);

						cout << "You have " << numberCitiesPowered << " cities powered" << endl;
						player->printPlayerInfo();
						break;
					}
					else if (poweredPlants[i] == choice) {
						cout << "You have already powered that plant!" << endl << endl;
						break;
					}
				}


			}

			if (numberCitiesPowered > player->getHouseCounter()) {
				cout << "You can only power cities that you own" << endl;
				numberCitiesPowered = player->getHouseCounter();
			}
			//Player gets paid according to number of cities they supply
			player->addElectro(numberCitiesPowered);

		}
		//Player chooses to power no cities
		else {
			player->addElectro(0);// No supply decision taken---> no elektros in return
		}
	}

}


