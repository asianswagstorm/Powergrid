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
#include "AggressiveStrategy.h"
#include "RandomStrategy.h"
#include "PassiveStrategy.h"

using namespace std;

Game::Game() {
	this->player_vector = std::vector<Player*>();;
	this->house_vector = std::vector<House>();
	this->powerplanthelper = new PowerPlantHelper();
	this->resourceMarket = new ResourceMarket();
	this->isEndGame = false;
}

//need to save the round number for load
Game::Game(std::vector<Player*> player_vector, Map *map) {
	this->round = 1; //player's first game round , set round as 2 to test load game
	this->player_vector = player_vector;
	this->resourceMarket = new ResourceMarket();
	this->powerplanthelper = new PowerPlantHelper();
	this->house_vector;
	this->isEndGame = false;
}

Game::~Game() { //destructor
}
//should save passive player in game 
		//[0,1] ---reverse --- [1,0] even
		//[0,1,2] ---reverse --- [2,1,0] odd
		//[0,1,2,3] ---reverse --- [3,2,1,0] even 
		//[0,1,2,3,4] ---reverse --- [4,3,2,1,0] odd
		//[0,1,2,3,4,5] ---reverse --- [5,4,3,2,1,0] even 


Player * Game::getPassivePlayer() {
	return this->passivePlayer;
}

void Game::setPassivePlayer(Player * passivePlayer) {
	this->passivePlayer = passivePlayer;
}

Player * Game::getAggressivePlayer() {
	return this->aggresivePlayer;

}
void Game::setAggressivePlayer(Player * aggresivePlayer) {
	this->aggresivePlayer = aggresivePlayer;
}

Player * Game::getRandomPlayer() {
	return this->randomPlayer;

}
void Game::setRandomPlayer(Player * randomPlayer) {
	this->randomPlayer = randomPlayer;
}

Game * Game::loadGame(int numPlayers) {
	player_vector = IOFile::loadPlayer();

	//Load map
	mapreader map;
	string mapFileName;
	std::cout << "Enter map file name not including .txt" << std::endl;
	cin >> mapFileName;

	map.readMap(mapFileName);

	numPlayers = player_vector.size();

	for (int i = 0; i < numPlayers; i++) {
		SummaryCard *sc = new SummaryCard();
		std::cout << endl << "===========Here is player" << i + 1 << "'s summary card=============" << std::endl << std::endl;
		sc->SummaryCardInfo();
	}
	powerplanthelper = new PowerPlantHelper(); // should show only 8 // Also should keep track of discarded cards or cards already in game. 
	powerplanthelper->PowerPlantHelper::setPPV(IOFile::loadPowerplants(player_vector));
	this->house_vector = IOFile::loadPlayerHouse(player_vector);//load all houses
	this->resourceMarket = IOFile::loadResourceMarket();
	
	return this;
}

Game * Game::setUpGame() {
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
							//Map theMap = Map(color);
							Map::instance()->createMap(color);
							isValidColorInput = true;
							break;
						}
					}
				}
				else {
					//Map theMap = Map(color);
					Map::instance()->createMap(color);
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
		IOFile::savePowerplants(powerplanthelper->getPPV());

		Area::setGameAreas(areas);
		//save players 
		IOFile::savePlayer(player_vector);
		//save fresh resource
		IOFile::saveResourceMarket(resourceMarket);
		//create map
		//Save map to map.txt
		IOFile::saveMap(); //load map should read the edges too

	}
	return this;
}

void Game::setRound(int round) {
	this->round = round;
}
int Game::getRound() const {
	return round;
}

void Game::determinePlayerOrder() {

	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	output << std::endl <<"------------Phase 1------------" << std::endl;
	
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
		output << endl << "------------------PLAYER ORDER ----------------" << endl;
		for (Player* player : this->player_vector) {
			std::cout << player->getName() << ", " << player->getHouseCounter() << " Houses, " << player->getnumOfPowerPlants() << " PowerPlants. " << std::endl;
			output << player->getName() << ", " << player->getHouseCounter() << " Houses, " << player->getnumOfPowerPlants() << " PowerPlants. " << std::endl;
		}

		break;
	}
	}
	output << std::endl << "--------END  Phase 1------------" << std::endl << std::endl;
	notify(); //Subject notify
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
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	output << std::endl<< "------------Phase 2------------" << std::endl << std::endl;
	
	//TO DO: SAVE THE RESOURCE POWERPLANTS WON TO FILE WITH THE PLAYER WHO OWNS IT.
	int AuctionWinner =-1, player_index = -1, auction_bid = -2, temp = 0;
	string response; //response= would you like to but a plant? //used to reset the response when a player responds
	string bid_response = ""; // do you want to join the auction war for a powerplant
	std::vector<Player*> player_with_Auction_vector;
	int numPlayers = this->player_vector.size();
	
	this->setAggressivePlayer(new Player(player_vector[0], new AggressiveStrategy(player_vector[0])));
	int aggresiveBid = this->getAggressivePlayer()->executeStrategy();

	this->setPassivePlayer(new Player(player_vector[1], new AggressiveStrategy(player_vector[1])));
	int passiveResponse = this->getPassivePlayer()->executeStrategy();
	
	if (numPlayers >= 3) //set 3rd player as random strategy
	{
		this->setRandomPlayer(new Player(player_vector[2], new RandomStrategy(player_vector[2])));
	}

	//reset the auction status
	for (int j = 0; j < numPlayers; j++) {
		//player_vector[j]->resetAuction();
		player_vector[j]->setAuction(false);
		player_vector[j]->setPass(false);
	}
	
	for (int i = 0; i < numPlayers; i++) { //loop every player to let them buy powerplants
		//first player is the aggressive player
		//second player is the aggressive player
		
		Player * p = player_vector[i];
		
		bool isInActual = false;
		bool canAfford = false;

		player_index = (int)i; //tracking players
		int init_playerBid;

		//reset auction again.
		for (int q = 0; q < numPlayers; q++) {
			player_vector[q]->resetAuction();

		}
		// if already bought powerplant, skip player.
		if (p->getPass() == true) {
			//player_vector[i]->auction(); //set auction = true
			p->setAuction(false);
			player_with_Auction_vector.push_back(player_vector[i]);
			continue; //gets out of the loop
		}
		std::cout << std::endl << "PHASE 2 POWERPLANT AUCTIONING" << std::endl;
		powerplanthelper->PowerPlantHelper::printPPMarket();

		if (p->getPass() == false) {
			if (i == 0)
				std::cout << std::endl << p->getName() << " is the first person to start the bid according to the player order rules. " << std::endl << std::endl;

			else {
				//check if previous player has passed on bid
				if (player_vector[i - 1]->getPass() == true) { //passed up on starting a bid. 
					player_index--; //skip the player
				}
				std::cout << std::endl << p->getName() << "'s turn. To start the bid " << std::endl;
			}
		}

		if (p->getPass() == true && p == player_vector[numPlayers - 1]) {
			break;
		}

		response = "";
		
		
		if (Game::getRound() >= 1) { // first round player must buy powerplant , I set round = 2 for testing in main. 
			while (response != "yes" && response != "no") {
				std::cout << p->getName() << ", do you want to auction on a powerplant (yes/no): ";
				output << p->getName() << ", do you want to auction on a powerplant (yes/no): " <<std::endl;

				if (p->getName() == this->getAggressivePlayer()->getName()) { response = "yes"; } //aggressive Player
				
				else if (p->getName() == this->getPassivePlayer()->getName() || passiveResponse == -1) {
					std::cout << std::endl  << std::endl << p->getName() << " is a Passive Player this player has passed on the auction" << std::endl;
					output << std::endl  << std::endl << p->getName() << " is a Passive Player this player has passed on the auction" << std::endl;
					response = "no"; } //passive Player
			
				else if (p->getName() == this->getRandomPlayer()->getName()){//random Player
					std::cout << std::endl << std::endl << p->getName() << " is a Random Player this player will choose a random bid in Actual Market" << std::endl;
					output << std::endl << std::endl << p->getName() << " is a Random Player this player will choose a random bid in Actual Market" << std::endl;
					response = "yes";
				} 
				
				else{
				cin >> response; std::cout << endl;
				}
			}

			if (response == "no") {
				std::cout << std::endl<<  player_vector[i]->getName() << " has passed on auctioning a power plant." << std::endl;
				output<< std::endl << player_vector[i]->getName() << " has passed on auctioning a power plant." << std::endl;
				p->pass(); //passing the oppurtunity to buy a powerplant
				p->setAuction(false);
				continue;
			}// end no
		}//end if round
		if (response == "yes") {
			p->auction(); //has an auction
			p->setPass(false);
			//player_vector[i]->setPass(false); //Didnt pass on buying a powerplant
			while (isInActual == false || canAfford == false)
			{ //if invalid bid (inssuficient fund or powerplant not in actual market
				std::cout << player_vector[i]->getName() << " currently has " << p->getElectro() << " elektros " << std::endl << std::endl;;
				std::cout << std::endl <<  "Enter a bid less than equal to max powerplant card number in actual market." << std::endl << "(This is the minimum bid in Electros to purchase the powerplant) : " << std::endl << std::endl;

				//Aggressive Strategy
				if(p->getName() == this->getAggressivePlayer()->getName()){
				std::cout << std::endl << this->getAggressivePlayer()->getName() << " is an Aggressive Player this player always chooses to bid on highest powerplant in Actual" << std::endl << std::endl;
				output << std::endl << this->getAggressivePlayer()->getName() << " is an Aggressive Player this player always chooses to bid on highest powerplant in Actual" << std::endl << std::endl;
				init_playerBid = aggresiveBid;
				}

				//Random Strategy
				else if (p->getName() == this->getRandomPlayer()->getName()) {
					std::cout << std::endl << this->getRandomPlayer()->getName() << " is a Random Player this player always chooses to bid on a random powerplant in Actual" << std::endl << std::endl;
					output << std::endl << this->getRandomPlayer()->getName() << " is a Random Player this player always chooses to bid on a random powerplant in Actual"  << std::endl << std::endl;
					init_playerBid = this->getRandomPlayer()->executeStrategy();

					std::cout << std::endl << this->getRandomPlayer()->getName() << " has chosen to bid for powerplant " << init_playerBid << std::endl << std::endl;
					output << std::endl << this->getRandomPlayer()->getName() << " has chosen to bid for powerplant " << init_playerBid << std::endl << std::endl;
				}

				else{
				std::cin >> init_playerBid;
				}
				isInActual = powerplanthelper->PowerPlantHelper::isPPActual(init_playerBid);
				canAfford = (p->getElectro() > init_playerBid);

				//check if in actual market.
				if (isInActual == false) {
					std::cout << endl << "!!!! This powerplant card is not in the Actual Market, INVALID BID" << endl << endl;
				}
				else if (canAfford == false) {
					std::cout << endl << "!!!! Insufficient funds, PowerPlant: " << init_playerBid << " costs " << init_playerBid << " Elektros" << endl;
					std::cout << "You only have " << p->getElectro() << " Elektros " << std::endl << std::endl;

					//aggressive player will always try to bid highest to get out of cant afford do this
					if (i == 0) {
						std::cout << std::endl << "Aggressive Player Cannot afford the bid for powerplant " << init_playerBid << std::endl << std::endl;
						output<< std::endl << "Aggressive Player Cannot afford the bid for powerplant " << init_playerBid << std::endl << std::endl;
						p->setAuction(false);
						player_index++;
						break;
					}
				}
				std::cout << "Correct Input, card " << init_playerBid << " is in actual market." << std::endl << std::endl;
			}//end while
		}//end response yes
	//auction while  
		while (player_index != numPlayers) { // while not end of player round

			//cout << endl << " Numb Players : " << numPlayers << endl << endl;
			//cout << " players with auction: " << player_with_Auction_vector.size() << endl << endl; //2 ?
			//cout << " player index: " << player_index << endl;
			int playersWithAuction = player_with_Auction_vector.size();

			//determine the winner
			if (player_index == numPlayers - 1 || numPlayers - playersWithAuction == 1) { // if last player or last player has no auction

				int k = 0;
				for (int j = 0; j < numPlayers; j++) {

					if (player_vector[j]->getAuction() == true) {//first is always false
						AuctionWinner = k;
						//std::cout << endl << "Winner is: " << AuctionWinner << endl;
					}
					k++;
				}
				break;
			}

			std::cout << std::endl << "------------ Starting Auction -----------" << std::endl << std::endl;
			output << std::endl << "------------ Starting Auction -----------" << std::endl << std::endl;
			if (p->getElectro() < init_playerBid) { 
				std::cout << p->getName() << "Insufficient funds to bid" << std::endl;
				player_index++;
				p->setAuction(false);
				continue;
			}

			if (p->getPass() == false || i == 0) { //should always get next unless pass = true

				p = getNextPlayer(*p);
			}

			if (temp == 0) {
				temp = init_playerBid;
			}

			std::cout << "The Current Bid for powerplant : #" << temp << " is " << init_playerBid << " Elektros" << endl;
			output << "The Current Bid for powerplant : #" << temp << " is " << init_playerBid << " Elektros" << endl;
			std::cout << p->getName() << " Would you wish to bid on this powerplant? Type yes or no " << endl;
			
			if (p->getName() == this->getPassivePlayer()->getName() ) { 
				std::cout << std::endl  << std::endl << std::endl << p->getName() << " is a Passive Player this player has passed on the bid" << std::endl << std::endl;
				output << std::endl << std::endl << std::endl << p->getName() << " is a Passive Player this player has passed on the bid" << std::endl << std::endl;
				bid_response = "no"; } //passive Player
			
			if (p->getName() == this->getRandomPlayer()->getName()) {
				std::cout << std::endl << std::endl << std::endl << p->getName() << " is a Random Player this player will always join an auction" << std::endl << std::endl;
				output << std::endl << std::endl << std::endl << p->getName() << " is a Random Player this player will always join an auction" << std::endl << std::endl;
				bid_response = "yes";
			} //random Player
			
			else if(p->getName() != this->getRandomPlayer()->getName() && p->getName() != this->getPassivePlayer()->getName())
			std::cin >> bid_response;

			if (bid_response == "yes") {//auction is true
				std::cout << "Please enter the amount you want to bid for powerplant: " << temp << std::endl;
				
				if (p->getName() == this->getRandomPlayer()->getName()) {//Random
					auction_bid = this->getRandomPlayer()->executeStrategy();
					std::cout << std::endl << this->getRandomPlayer()->getName() << " chose " << auction_bid << std::endl;
					output << std::endl << this->getRandomPlayer()->getName() << " chose " << auction_bid << std::endl;
				}
				else
				std::cin >> auction_bid;

				bool lowBid = auction_bid <= init_playerBid;
				bool cantAfford = p->getElectro() < init_playerBid;

				if (lowBid) { //can no longer bid
					std::cout << std::endl << "This bid is too low, you lose the chance to buy a powerplant this round." << std::endl;
					output << std::endl << "This bid is too low, you lose the chance to buy a powerplant this round." << std::endl;
					//p->setAuction(false); // set auction to be false
					p->setAuction(false);
					player_with_Auction_vector.push_back(p);
					player_index++;

				}
				else if (cantAfford) { //can no longer bid
					std::cout << std::endl << "You do not have enough electro to buy this powerplant." << std::endl;
					output << std::endl << "You do not have enough electro to buy this powerplant." << std::endl;
					//p->setAuction(false); // set auction to be true
					p->setAuction(false);
					player_with_Auction_vector.push_back(p);
					player_index++;
				}

				if (lowBid == false && cantAfford == false) { //If won auction

					init_playerBid = auction_bid;

					std::cout << "The bid for plant: " << temp << " changed to: " << init_playerBid << std::endl << std::endl;
					//p->setAuction(false); // set auction to be false used to determine auction winner
					p->auction();
					player_with_Auction_vector.push_back(p);
					player_index++;
				}

			}//end yes bid_response

			if (bid_response == "no") { //Don't want to join the bidding war, should go to next.
				temp = temp;
				std::cout << std::endl << std::endl << p->getName() << " has passed on joining the auction for powerplant:" << temp << std::endl;
				output<< std::endl << std::endl << p->getName() << " has passed on joining the auction for powerplant:" << temp << std::endl;
				p->setAuction(false); // set auction to be true
				player_with_Auction_vector.push_back(p);
				player_index++;
			}

		}//end auction while 	

		//int powerplantNum = temp;
		//Errors
		if (temp == 0) {
			temp = init_playerBid;
		}
		if (AuctionWinner == -1) //no winner in this case, aggressive player cannot afford the bid
			continue;

		std::cout << player_vector[AuctionWinner]->getName() << " won the auction for powerplant: " << temp << std::endl << std::endl;
		output << player_vector[AuctionWinner]->getName() << " won the auction for powerplant: " << temp << std::endl << std::endl;
		//player_vector[AuctionWinner]->setAuction(false);

		player_vector[AuctionWinner]->setPass(true);
		player_vector[AuctionWinner]->addPowerPlant(powerplanthelper->removePowerPlant(temp, player_vector[AuctionWinner]));
		player_vector[AuctionWinner]->setnumOfPowerPlants(player_vector[AuctionWinner]->getnumOfPowerPlants());//not working
		player_vector[AuctionWinner]->removeElectro(temp);
		temp = 0;

	}//main for loop done
	std::cout << std::endl << "-------------Player Stats Updated------------------" << std::endl << std::endl;
	output << std::endl << "-------------END PHASE 2 PowerPlants Updated------------------" << std::endl << std::endl;
	IOFile::savePlayer(player_vector);
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		player_vector[i]->printPlayerInfo();
	}
	notify(); //Subject notify
}

//Step 3 - Buy resources from the resource market. 
void Game::buyResources() {

	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	output << "------------Phase 3------------" << std::endl;
	
	std::cout << std::endl;
	std::cout << "BUYING RESOURCES" << std::endl;
	std::cout << std::endl;

	string materialChoice = "";

	int qty;

	this->setAggressivePlayer(new Player(player_vector[0], new AggressiveStrategy(player_vector[0])));

	this->setPassivePlayer(new Player(player_vector[1], new AggressiveStrategy(player_vector[1])));

	if (player_vector.size() >= 3) //set 3rd player as random strategy
	{
		this->setRandomPlayer(new Player(player_vector[2], new RandomStrategy(player_vector[2])));
	}

	reverse(player_vector.begin(), player_vector.end()); //from <algorithm>

	//std::cout << std::endl <<  "Passive Player: " << passivePlayer->getName() << std::endl << std::endl;

	bool validMaterialChoice = false;
	for (Player* p : player_vector) {
		std::cout << "Player order reversed: " << p->getName() << std::endl << std::endl;
		while (true) {
			this->resourceMarket->ResourceMarket::showRemaining();

			while (validMaterialChoice == false) {
				std::cout << std::endl << std::endl << p->getName() << "'s turn, choose what you want to buy: " << endl << "(coal, oil, garbage or uranium)" << " When you finish enter f  " << endl;
				output << std::endl << std::endl << p->getName() << "'s turn, choose what you want to buy: " << endl << "(coal, oil, garbage or uranium)" << endl;
				
				if (p->getName() == this->getPassivePlayer()->getName()) {
					std::cout << std::endl << p->getName() << " is a passive player, they will not be buying any materials " << std::endl << std::endl;
					output << std::endl << p->getName() << " is a passive player, they will not be buying any materials " << std::endl << std::endl;
					materialChoice = "f";
				}
				else
				std::cin >> materialChoice; std::cout << endl;
				
				materialChoice[0] = toupper(materialChoice[0]); //capitilize the first letter

				if (materialChoice == "Coal" || materialChoice == "Oil" || materialChoice == "Uranium" || materialChoice == "Garbage" || materialChoice == "Uranium" || materialChoice == "F")
					if (materialChoice == "F") {
						std::cout << std::endl << p->getName() << " is done their turn." << std::endl;
						output << std::endl << p->getName() << " is done their turn." << std::endl;
					}
					validMaterialChoice = true;
			}
			//check invalid materialChoice

			if (materialChoice != "F") {
				std::cout << std::endl << "How many " << materialChoice << " do you want to buy: ";
				output << std::endl << "How many " << materialChoice << " do you want to buy: ";
				std::cin >> qty;

				if (resourceMarket->getMarketCost(materialChoice, qty) == -1) {
					std::cout << "Player Cannot Afford to buy the resource" << endl;
					output << "Player Cannot Afford to buy the resource" << endl;
					system("pause");
					continue;
				}
				//first round only has 3 coal
				//Buy the resource  validateResourcePurchase in player class 
				//validateResourcePurchase(int cost, int quantity, string type)

				if (p->validateResourcePurchase(resourceMarket->getMarketCost(materialChoice, qty), qty, materialChoice)) {
					//resource added and electro removed in validateResourcePurchase
					std::cout << "Cost was: " << resourceMarket->getMarketCost(materialChoice, qty) << " elektros." << std::endl;
					std::cout << std::endl << "Here is how much elektros you have after buying " << qty << " " << materialChoice << ": " << p->getElectro() << "$" << std::endl;
					std::cout << "You current have " << p->getResourceQuantity(materialChoice) << " " << materialChoice << std::endl;

					output << "Cost was: " << resourceMarket->getMarketCost(materialChoice, qty) << " elektros." << std::endl;
					output << std::endl << "Here is how much elektros you have after buying " << qty << " " << materialChoice << ": " << p->getElectro() << "$" << std::endl;
					output << "You current have " << p->getResourceQuantity(materialChoice) << " " << materialChoice << std::endl;

					resourceMarket->updateMarket(materialChoice, qty);
					IOFile::saveResourceMarket(resourceMarket);
					IOFile::savePlayer(player_vector);
				}
				validMaterialChoice = false;
			}
			else {
				validMaterialChoice = false;
				break;
			}
		}//end while true
	}//end for
	output << std::endl <<"--------------------- END Phase 3 ----------" << std::endl  << std::endl;
	notify(); //Subject notify
}

void::Game::buildHouse() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	output << std::endl << "------------Phase 4------------" << std::endl << std::endl ;
	
	bool buyhouseloop = false;
	//TO DO: REMOVE THE HOUSES ALREADY BOUGHT, AND ONLY SHOW AVAILABLE ONES
	string response;
	vector<House> house_vector;
	vector<int> house_index = IOFile::getMapIndexs();

	//Passive Player
	int passiveResponse = this->getPassivePlayer()->executeStrategy();
	
	//std::cout << "houseSize: " << house_index.size() << std::endl; //7
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		Player * p = player_vector[i];
		//Map theMap = Map(p->Player::getAreaColor());
		Map::instance()->createMap(p->Player::getAreaColor());

		std::cout << p->getName() << " Would you like to build a house in: " << p->Player::getAreaColor() << " area " << endl;
		std::cout << "yes or no." << std::endl;
		//passive
		
		if (passiveResponse == -1 || p->getName() == this->getPassivePlayer()->getName()) {
			std::cout << std::endl << p->getName() << " is a passive player, they will not be buying any Houses " << std::endl << std::endl;
			output << std::endl << p->getName() << " is a passive player, they will not be buying any Houses " << std::endl << std::endl;
			response = "no";
		}
		else
		std::cin >> response;

		if (response == "no") {
			std::cout << p->getName() << " has chosen not to buy a house" << endl;
			output << p->getName() << " has chosen not to buy a house" << endl;
		}

		if (response == "yes") {
			buyhouseloop = true;
			while (buyhouseloop == true) {
				int houseCount = p->Player::getHouse()->HouseHelper::getHouse();

				//if player does not have enough electro to purchase 1 house of 10 elektro
				if (!p->hasEnoughtElektro(10)) {
					std::cout << p->getName() << " Does not have enough elektro to build a house, less than 10 elektro" << endl;
					buyhouseloop = false;
					break;
				}

				//if player has no houses yet

				std::cout << "You can build in these Cities:" << endl;

				for (unsigned int k = 0; k < house_index.size(); k++) { // should shoe all 
					if (Map::getCityName(house_index[k]) == "")
						std::cout << "";
					else
						std::cout << "Map Index: " << Map::getIndexNumber(house_index[k]) << ", City Name: " << Map::getCityName(house_index[k]) << endl;
				}

				unsigned int index;
				std::cout << std::endl << "Please choose an Map Index you want to build a house in, refer to map file" << endl;
				std::cout << "Map Index: ";

				std::cin >> index;

				while (!std::count(house_index.begin(), house_index.end(), index)) { //bool function is in 
					std::cout << "Invalid Input enter a valid one" << std::endl;
					std::cin >> index;
				}

				std::cout << "You currently have " << p->getElectro() << " elektro a house costs 10 elektros" << endl;

				House house(index, Map::getCityName(index));
				house_vector.push_back(house);
				p->removeElectro(10);
				//house.setisPowered(true); testing
				p->Player::getHouse()->HouseHelper::addHouse(house);
				p->Player::getHouse()->HouseHelper::setHouse(p->Player::getHouse()->HouseHelper::getHouseVector().size());

				std::cout << endl << "Purchase completed" << endl;
				std::cout << "You now have " << p->getElectro() << " elektro" << endl;
				std::cout << "You now have " << p->Player::getHouse()->HouseHelper::getHouseVector().size() << " houses" << endl;

				std::cout << p->getName() << " would you like to build another house?." << endl;
				std::cout << "yes or no." << endl;
				std::cin >> response;

				if (response == "no") {
					std::cout << p->getName() << " has chosen not to buy another house" << endl;
					buyhouseloop = false;
					p = getNextPlayer(*p);
				}
			} // while true
		}
	}
	std::cout << std::endl << "-------------Player Stats Updated------------------" << std::endl << std::endl;
	IOFile::savePlayer(player_vector); // needs to add the new houses
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		player_vector[i]->printPlayerInfo();
	}
	//save houses
	IOFile::savePlayerHouse(house_vector, player_vector);
	output << std::endl << "------------END Phase 4------------"  << std::endl << std::endl;
	notify(); //Subject notify
}

int Game::getPayment(int numPoweredHouse) {

	switch (numPoweredHouse)
	{
	case 0:
		return 10;
		break;
	case 1:
		return 22;
		break;
	case 2:
		return 33;
		break;
	case 3:
		return 44;
		break;
	case 4:
		return 54;
		break;
	case 5:
		return 64;
		break;
	case 6:
		return 73;
		break;
	case 7:
		return 82;
		break;
	case 8:
		return 90;
		break;
	case 9:
		return 98;
		break;
	case 10:
		return 105;
		break;
	case 11:
		return 112;
		break;
	case 12:
		return 118;
		break;
	case 13:
		return 124;
		break;
	case 14:
		return 129;
		break;
	case 15:
		return 134;
		break;
	case 16:
		return 138;
		break;
	case 17:
		return 142;
		break;
	case 18:
		return 145;
		break;
	case 19:
		return 148;
		break;
	case 20:
		return 150;
		break;
	default:
		return 150;
		break;

	}
}

void Game::bureaucracy() {

	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	output << std::endl << "------------Phase 5------------" << std::endl << std::endl;
	
	//players earn cash(done)
	//re-supply the resource market, // did not do
	//remove a power plant from the power plant market, replacing it with a new one from the stack (done) 

	vector<House> house_vector = IOFile::loadPlayerHouse(player_vector);
	//needs refill
	int houseIndex;

	std::cout << "*****************************************************************" << std::endl;
	std::cout << " PART 5: BUREAUCRACY" << endl;
	std::cout << "*****************************************************************" << std::endl;

	string powerDecision;
	int numPoweredHouses = 0;
	//Passive Player
	int passiveResponse = this->getPassivePlayer()->executeStrategy();
	reverse(player_vector.begin(), player_vector.end());
	for (Player* p : player_vector) {
		//Map theMap = Map(p->Player::getAreaColor()); // important
		Map::instance()->createMap(p->Player::getAreaColor());
		// each player has one
		//Money received depends on the number of powered houses.
		//<---->If no house powered ---> the automatically 10 elektro.
		//- Giving them the ability to decide how many houses they want to power based on their resources.
		std::cout << "**********************************************************************************************************************" << std::endl;
		std::cout << p->getName() << " has " << p->Player::getHouse()->HouseHelper::getHouse() << " houses. " << std::endl;
		output << p->getName() << " has " << p->Player::getHouse()->HouseHelper::getHouse() << " houses. " << std::endl;

		if (p->Player::getHouse()->HouseHelper::getHouse() > 0) {
			std::cout << "Here are all of " << p->getName() << " houses: " << std::endl << std::endl;
			output << "Here are all of " << p->getName() << " houses: " << std::endl << std::endl;

			for (unsigned int i = 0; i < p->Player::getHouse()->HouseHelper::getHouseVector().size(); i++) {
				std::cout << p->Player::getHouse()->HouseHelper::getHouseVector()[i].getIndex() << " (" << p->Player::getHouse()->HouseHelper::getHouseVector()[i].getLocation() << ") " << ",";
				output << p->Player::getHouse()->HouseHelper::getHouseVector()[i].getIndex() << " (" << p->Player::getHouse()->HouseHelper::getHouseVector()[i].getLocation() << ") " << ",";
				
				/*if(p->Player::getHouse()->HouseHelper::getHouseVector()[i].getisPowered() == true)
				{
					powered_house_vector.push_back(p->Player::getHouse()->HouseHelper::getHouseVector()[i]);
				}*/
			}//end for

			std::cout << std::endl << "Attention: You can only power cities that you own." << endl;
			std::cout << "**********************************************************************************************************************" << endl;
			std::cout << "Do you want to power any Cities?";
			std::cout << "(yes or no)";
		
			//passive player refusing to power a house 
			if (passiveResponse == -1 || p->getName() == this->getPassivePlayer()->getName()) {
				std::cout << std::endl << p->getName() << " is a passive player, they will not be buying any Houses " << std::endl << std::endl;
				output << std::endl << p->getName() << " is a passive player, they will not be buying any Houses " << std::endl << std::endl;
				powerDecision = "no";
			}
			else
			std::cin >> powerDecision; std::cout << endl;
			
			//If yes, player will power cities
			if (powerDecision == "yes") {

				for (unsigned int k = 0; k < p->Player::getHouse()->HouseHelper::getHouseVector().size(); k++) {
					if (p->Player::getHouse()->HouseHelper::getHouseVector()[k].getisPowered() == false)
						std::cout << std::endl << "Here are your nonpowered houses: " << std::endl << p->Player::getHouse()->HouseHelper::getHouseVector()[k].getIndex() << " (" << p->Player::getHouse()->HouseHelper::getHouseVector()[k].getLocation() << ") " << ",";
						output << std::endl << "Here are your nonpowered houses: " << std::endl << p->Player::getHouse()->HouseHelper::getHouseVector()[k].getIndex() << " (" << p->Player::getHouse()->HouseHelper::getHouseVector()[k].getLocation() << ") " << ",";
				}
				std::cout << "Which house do you want to power?" << std::endl; std::cout << endl;
				std::cin >> houseIndex;
				std::cout << endl;
				int indexindex;
				for (unsigned int t = 0; t < house_vector.size(); t++) {
					if (houseIndex == house_vector[t].getIndex()) {
						indexindex = t;
					}
				}

				for (unsigned int j = 0; j < p->Player::getHouse()->HouseHelper::getHouseVector().size(); j++) {
					if (houseIndex == p->Player::getHouse()->HouseHelper::getHouseVector()[j].getIndex() && p->Player::getHouse()->HouseHelper::getHouseVector()[j].getisPowered() == false) {

						//p->Player::getHouse()->HouseHelper::getHouseVector()[j].setisPowered(true);
						House house(houseIndex, Map::getCityName(houseIndex));
						house.setisPowered(true);
						house_vector.erase(house_vector.begin() + indexindex);
						//remove the duplicate before pushing new one in 
						house_vector.push_back(house);
						p->Player::getHouse()->HouseHelper::addHouse(house);

					}

					if (p->Player::getHouse()->HouseHelper::getHouseVector()[j].getisPowered() == true) {
						numPoweredHouses++;
						std::cout << "Num Powered Houses: " << numPoweredHouses << std::endl;
					}
				}//end for

				std::cout << "Adding " << Game::getPayment(numPoweredHouses) << " Elektro to your wallet." << std::endl;
				output << "Adding " << Game::getPayment(numPoweredHouses) << " Elektro to your wallet." << std::endl;
				
				p->setElectro(p->getElectro() + Game::getPayment(numPoweredHouses));
				p->printPlayerInfo();

			}//end yes
			else if (powerDecision == "no") {
				p->addElectro(0);
			}//end no

		}//end if house > 0
		
		//passive player should be here unless we gave them a house, since a passive player does nothing but refuse everything
		else if (p->Player::getHouse()->HouseHelper::getHouse() <= 0 && powerDecision != "no" && powerDecision != "yes") {
			std::cout << "You have no houses to power!" << std::endl;
			std::cout << "You are offered 10 Elektros" << std::endl  << std::endl;

			output << p->Player::getName() <<"You have no houses to power!" << std::endl;
			output << "You are offered 10 Elektros" << std::endl << std::endl;

			p->setElectro(p->getElectro() + Game::getPayment(0));
			p->printPlayerInfo();
		}//end else 

	}//end for

	IOFile::savePlayer(player_vector); // needs to add the new houses
	std::cout << "house_vector size: " << house_vector.size() << std::endl; // should be all the houses + powered yes	
	IOFile::savePlayerHouse(house_vector, player_vector); //powered_house_vector not all is powered
	
	output << "------------END Phase 5------------" << std::endl << std::endl;
	notify(); //Subject notify
}
