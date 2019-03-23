#pragma once
#include "Player.h"
#include "Map.h"
#include "PowerPlant.h"

#include <iostream>
using namespace std;
class Game {
public:
	Game();
	Game(std::vector<Player*> player_vector, Map *map);
	~Game();

	void setTurn(int turn);
	int getTurn();
	//void playerOrder(std::vector<Player*> player_vector);
	void buyPowerPlant();

private:
	int turn;
	std::vector<Player*> player_vector;
	
	bool step2;
	bool step3;
	bool isEndGame = false;

};