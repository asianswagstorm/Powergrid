#pragma once
#include "Player.h"
#include "Map.h"
#include "Subject.h"
#include "PowerPlant.h"
#include "PowerPlantHelper.h"
#include "Resource.h"
#include "SummaryCard.h"
#include "ResourceMarket.h"
#include "Area.h"
#include "IOFile.h"

#include <iostream>
using namespace std;
class Game : public Subject {
public:
	
	Game() {
		this->player_vector = std::vector<Player*>();;
		this->house_vector = std::vector<House>();
		this->powerplanthelper = new PowerPlantHelper();
		this->resourceMarket = new ResourceMarket();
		this->isEndGame = false;
	}
	Game(std::vector<Player*> player_vector, Map *map);
	~Game();

	void loadGame(int);
	void setUpGame();

	void setRound(int round);
	int getRound() const;
	void determinePlayerOrder();
	int getFirstPlayer(std::vector<Player*> player_vector, int i);
	void swapPlayers(Player& player1, Player& player2);
	Player * getNextPlayer(Player& player);
	void buyPowerPlant();
	void buyResources();
	void bureaucracy();
	void buildHouse();
	int getPayment(int numPoweredHouse);

private:
	
	int round;
	std::vector<Player*> player_vector;
	std::vector<House> house_vector;
	PowerPlantHelper * powerplanthelper;
	ResourceMarket * resourceMarket;
	bool isEndGame = false;

};

