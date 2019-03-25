#pragma once
#include "Player.h"
#include "Map.h"
#include "PowerPlant.h"
#include "PowerPlantHelper.h"
#include "Resource.h"
#include "SummaryCard.h"
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

	void buyPowerPlant();
	



private:
	int round;
	std::vector<Player*> player_vector;
	PowerPlantHelper * powerplanthelper;
	//bool phase2;
	//bool phase2;
	bool isEndGame = false;

};