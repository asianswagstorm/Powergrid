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

using namespace std;

Game::Game() {
	this->resourceMarket = new ResourceMarket();
	this->powerplanthelper = new PowerPlantHelper();// this would create new ppv every time update the cards

	round = 0; //default contructor, no game so no round 
}
//need to save the round number for load
Game::Game(std::vector<Player*> player_vector, Map *map) {
	this->round = 1; //player's first game round , set round as 2 to test load game
	this->player_vector = player_vector;
	this->resourceMarket = new ResourceMarket();
	this->powerplanthelper = new PowerPlantHelper();
	
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
	powerplanthelper->setPPV(IOFile::loadPowerplants());
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
		IOFile::savePowerplants(powerplanthelper->getPPV());

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

	//TO DO: SAVE THE RESOURCE POWERPLANTS WON TO FILE WITH THE PLAYER WHO OWNS IT.
	int AuctionWinner, player_index = -1, auction_bid = -2, temp = 0;
	string response; //response= would you like to but a plant? //used to reset the response when a player responds
	string bid_response = ""; // do you want to join the auction war for a powerplant
	std::vector<Player*> player_with_Auction_vector;
	
	int numPlayers = this->player_vector.size();
	//reset the auction status
	for (int j = 0; j < numPlayers; j++) {
		//player_vector[j]->resetAuction();
		player_vector[j]->setAuction(false);
		player_vector[j]->setPass(false);
	}

	for (int i = 0; i < numPlayers; i++) { //loop every player to let them buy powerplants
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

		if(p->getPass() == false){
		if (i == 0)
			std::cout << std::endl << p->getName() << " is the first person to start the bid according to the player order rules. " << std::endl << std::endl;

		else {
			//check if previous player has passed on bid
			if (player_vector[i - 1]->getPass() == true) { //passed up on starting a bid. 
				player_index--; //skip the player
			}
			std::cout << std::endl << p->getName() << "'s turn. " << std::endl;
			std::cout << "To start the bid " << std::endl;
		}
		}
		
		if (p->getPass() == true && p == player_vector[numPlayers - 1]) {
			break;
		}

		response = "";
		if (Game::getRound() >= 1) { // first round player must buy powerplant , I set round = 2 for testing in main. 
			while (response != "yes" && response != "no") {
				std::cout << p->getName() << ", do you want to auction on a powerplant (yes/no): ";
				cin >> response; std::cout << endl;
			}

			if (response == "no") {
				std::cout << player_vector[i]->getName() << " has passed on auctioning a power plant." << endl;
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
				std::cout << player_vector[i]->getName() << " currently has " << p->getElectro() << " elektros " << std::endl;
				std::cout << "Enter a bid less than equal to max powerplant card number in actual market." << std::endl << "(This is the minimum bid in Electros to purchase the powerplant) : " << endl;

				std::cin >> init_playerBid;

				isInActual = powerplanthelper->PowerPlantHelper::isPPActual(init_playerBid);
				canAfford = (p->getElectro() > init_playerBid);

				//check if in actual market.
				if (isInActual == false) {
					std::cout << endl << "!!!! This powerplant card is not in the Actual Market, INVALID BID" << endl << endl;
				}
				else if (canAfford == false) {
					std::cout << endl << "!!!! Insufficient funds, PowerPlant: " << init_playerBid << " costs " << init_playerBid << " Elektros" << endl;
					std::cout << "You only have " << p->getElectro() << " Elektros " << std::endl << std::endl;
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
			
			//cout << " Pass is " << p->getPass() << endl;
			
			if (p->getPass() == false) { //should always get next unless pass = true
				
				p = getNextPlayer(*p);
			}

			if (p->getElectro() < init_playerBid) {
				std::cout << p->getName() << "Insufficient funds to bid" << std::endl;
				player_index++;
				p->setAuction(false);
				continue;
			}
			if (temp == 0) {
				temp = init_playerBid;
			}

			std::cout << "The Current Bid for powerplant : #" << temp << " is " << init_playerBid << " Elektros" << endl;
			std::cout << p->getName() << " Would you wish to bid on this powerplant? Type yes or no " << endl;
			std::cin >> bid_response;

			if (bid_response == "yes") {//auction is true
				std::cout << "Please enter the amount you want to bid for powerplant: " << temp << std::endl;
				std::cin >> auction_bid;

				bool lowBid = auction_bid <= init_playerBid;
				bool cantAfford = p->getElectro() < init_playerBid;

				if (lowBid) { //can no longer bid
					std::cout << std::endl << "This bid is too low, you lose the chance to buy a powerplant this round." << std::endl;
					//p->setAuction(false); // set auction to be false
					p->setAuction(false);
					player_with_Auction_vector.push_back(p);
					player_index++;

				}
				else if (cantAfford) { //can no longer bid
					std::cout << std::endl << "You do not have enough electro to buy this powerplant." << std::endl;
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
				std::cout << p->getName() << " has passed on joining the auction for powerplant:" << temp << std::endl;
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
		std::cout << player_vector[AuctionWinner]->getName() << " won the auction for powerplant: " << temp << std::endl << std::endl;
		//player_vector[AuctionWinner]->setAuction(false);
		
		player_vector[AuctionWinner]->setPass(true);
		player_vector[AuctionWinner]->addPowerPlant(powerplanthelper->removePowerPlant(temp, player_vector[AuctionWinner]));
		player_vector[AuctionWinner]->setnumOfPowerPlants(player_vector[AuctionWinner]->getnumOfPowerPlants());
		player_vector[AuctionWinner]->removeElectro(temp);
		temp = 0;
		

	}//main for loop done
	std::cout << std::endl << "-------------Player Stats Updated------------------" << std::endl << std::endl;
	IOFile::savePlayer(player_vector);
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		player_vector[i]->printPlayerInfo();
	}
}

//Step 3 - Buy resources from the resource market. 
void Game::buyResources() {
	//TO DO: SAVE THE RESOURCE MARKET TO FILES AND LOAD THEM.
	std::cout << "------------Phase 3------------" << endl;
	std::cout << endl;
	std::cout << "BUYING RESOURCES" << endl;
	std::cout << endl;

	string materialChoice="";
	
	int qty;
	reverse(player_vector.begin(), player_vector.end()); //from <algorithm>
	bool validMaterialChoice = false;
	for (Player* p : player_vector) {
		std::cout << "Player order reversed: " << p->getName() << std::endl << std::endl;
		while (true) {
			this->resourceMarket->ResourceMarket::showRemaining();

			while (validMaterialChoice == false) {
				std::cout << std::endl << std::endl << p->getName() << "'s turn, choose what you want to buy: " << endl << "(coal, oil, uranium, or garbage)" << " When you finish please type f  " << endl;
				std::cin >> materialChoice; std::cout << endl;
				materialChoice[0] = toupper(materialChoice[0]); //capitilize the first letter


				if (materialChoice == "Coal" || materialChoice == "Oil" || materialChoice == "Uranium" || materialChoice == "Garbage" || materialChoice == "Uranium" || materialChoice == "F")
					validMaterialChoice = true;
			}
			//check invalid materialChoice

			if (materialChoice != "F") {
				std::cout << std::endl << "How many " << materialChoice << " do you want to buy: ";
				std::cin >> qty;

				if (resourceMarket->getMarketCost(materialChoice, qty) == -1) {
					std::cout << "Player Cannot Afford to buy the resource" << endl;
					system("pause");
					continue;
				}
				//first round only has 3 coal
				//Buy the resource  validateResourcePurchase in player class 
				//validateResourcePurchase(int cost, int quantity, string type)

				if (p->validateResourcePurchase(resourceMarket->getMarketCost(materialChoice, qty), qty, materialChoice)) {

					std::cout << "Cost was: " << resourceMarket->getMarketCost(materialChoice, qty) << " elektros." << endl;
					std::cout << endl << "Here is how much elektros you have after buying " << qty << " " << materialChoice << ": " << p->getElectro() << "$" << endl;
					std::cout << "You current have " << p->getResourceQuantity(materialChoice) << " " << materialChoice << endl;

					resourceMarket->updateMarket(materialChoice, qty); //error here 
				}
				validMaterialChoice = false;
			}
			else {
				validMaterialChoice = false;
				break;
			}
		}//end while true
	}//end for
}

void::Game::buildHouse() {
	//TO DO: REMOVE THE HOUSES ALREADY BOUGHT, SAVE TO FILE AND THEN PUSH TO VECTOR
	string response;
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		Player * p = player_vector[i];
		Map theMap = Map(p->Player::getAreaColor());
		std::cout << p->getName() << " Would you like to build a house in: " << p->Player::getAreaColor() << " area " << endl;
		std::cout << "yes or no." << std::endl;
		std::cin >> response;

		if (response == "yes") {

			int houseCount = p->Player::getHouse()->HouseHelper::getHouse();

			//if player does not have enough electro to purchase 1 house of 10 elektro
			if (!p->hasEnoughtElektro(10)) {
				std::cout << p->getName() << " Does not have enough elektro to build a house, less than 10 elektro" << endl;
				break;
			}

			//if player has no houses yet

			std::cout << "You can build in these Cities:" << endl;

			for (unsigned int k = 0; k < (player_vector.size()*7); k++) {
				if (Map::getCityName(k) == "")
					std::cout << "" ;
				else
				std::cout << "Map Index: "  << Map::getIndexNumber(k) << ", City Name: "<< Map::getCityName(k) <<endl;
			}

			int index;
			std::cout << std::endl << "Please choose an Map Index you want to build a house in, refer to map file" << endl;
			std::cout << "Map Index: ";

			std::cin >> index;

			while (index < 0 || index > (player_vector.size()*7)) {
				std::cout << "Invaid Input enter a valid one" << std::endl;
				std::cin >> index;
			}

			std::cout << "You currently have " << p->getElectro() << " elektro a house costs 10 elektros" << endl;

			House house(index, Map::getCityName(index));

			p->removeElectro(10);

			p->Player::getHouse()->HouseHelper::addHouse(house);
			p->Player::getHouse()->HouseHelper::setHouse(p->Player::getHouse()->HouseHelper::getHouseVector().size());

			std::cout << endl << "Purchase completed" << endl;
			std::cout << "You now have " << p->getElectro() << " elektro" << endl;
			std::cout << "You now have " << p->Player::getHouse()->HouseHelper::getHouseVector().size() << " houses" << endl;
			
			std::cout << p->getName() << " would you like to build another house?." << endl;
			std::cout << "yes or no." << endl;
			std::cin >> response;

		}
			if (response == "yes") {
			continue;
			}

			if (response == "no") {
				p = getNextPlayer(*p);
	
			}
	}
	std::cout << std::endl << "-------------Player Stats Updated------------------" << std::endl << std::endl;
	IOFile::savePlayer(player_vector); // needs to add the new houses
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		player_vector[i]->printPlayerInfo();
	}
}


void Game::bureaucracy() {
	//TO DO SUNDAY MARCH 31th!!!!
	/*
	//needs refill
	int choice;

	cout << "*****************************************************************" << endl;
	cout << " PART 5: BUREAUCRACY" << endl;
	cout << "*****************************************************************" << endl;

	string powerDecision;
	vector<int> numberCitiesPoweredAtEnd;

	reverse(player_vector.begin(), player_vector.end());
	for (Player* player : player_vector) {

		int poweredPlants[3] = { -1,-1,-1 }; //Initial status (no powered plants)
		//Money received depends on the number of powered houses.
		//<---->If no house powered ---> the automatically 10 elektro.
		//- Giving them the ability to decide how many houses they want to power based on their resources.
		std::cout << "**********************************************************************************************************************" << endl;
		std::cout << player->getName() << " has " << player->getHouse()->getHouse() << " houses." << endl;
		std::cout << "Attention: You can only power cities that you own, any powering except that will be a loss of resources." << endl;
		std::cout << "**********************************************************************************************************************" << endl;
		std::cout << "Do you want to power any Cities?";
		std::cout << "(yes or no)";
		std::cin >> powerDecision; cout << endl;

		//If yes, player will power cities
		if (powerDecision == "yes") {
			choice = -1;
			int numberCitiesPowered = 0;

			//case 1: no houses to power---> 10 elektros will be offered to the player
			if (player->getHouseCounter() == 0) {
				choice = 0;
				cout << "You have no cities to power!" << endl;
				cout << "You are offered 10 Elektros" << endl;
				
				player->setElectro(player->getElectro() + 10);

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
						numberCitiesPowered += player->getnumOfPowerPlants();

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
*/
}


