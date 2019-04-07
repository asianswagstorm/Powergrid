#pragma once
#include "Player.h"
#include "Map.h"
#include "PowerPlant.h"
#include "PowerPlantHelper.h"
#include "Resource.h"
#include "SummaryCard.h"
#include "ResourceMarket.h"
#include "Area.h"
#include "IOFile.h"

#include <iostream>
using namespace std;
class Game {
public:
	Game();
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