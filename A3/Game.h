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
	
	Game();
	Game(std::vector<Player*> player_vector, Map *map);
	~Game();

	Game * loadGame(int);
	Game * setUpGame();

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
	Player * getPassivePlayer();
	void setPassivePlayer(Player *);
	Player * getAggressivePlayer();
	void setAggressivePlayer(Player *);
	Player * getRandomPlayer();
	void setRandomPlayer(Player *);

	friend class ElektroView;
	friend class HouseView;
	friend class PowerPlantView;
	friend class ResourceView;

private:
	
	int round;
	std::vector<Player*> player_vector;
	std::vector<House> house_vector;
	PowerPlantHelper * powerplanthelper;
	ResourceMarket * resourceMarket;
	bool isEndGame = false;
	Player * passivePlayer; // player that says no to everything
	Player * aggresivePlayer; // player who bids on highest powerplant
	Player * randomPlayer; // player always picks random stuff
};

