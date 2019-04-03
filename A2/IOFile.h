#pragma once
#include "Player.h"
#include "Map.h"
#include <sstream>
class IOFile
{
public:
	IOFile();
	~IOFile();
	//save map inputs to map.txt
	static void saveMap();
	static void savePlayer(vector<Player*> player_vector);
	static std::vector<Player *> loadPlayer();
	static void readMapInput(string areaColor);
	static void addEdges();
	static void savePlayerOrder(vector<Player*> player_vector);
	
	//TO DO: 

	static void savePowerplants(vector<PowerPlant> * ppv);//1 file with writing in game or not True False
	static std::vector<PowerPlant> * loadPowerplants();
	static int splitString(string variable);

	static void savePlayerHouse(vector<House> house_vector, vector<Player*> player_vector);
	static void loadPlayerHouse();
	
	static void saveResourceMarket();
	static void loadResourceMarket();

	static void updatePlayerResources();
	
};


