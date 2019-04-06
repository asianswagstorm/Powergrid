#pragma once
#include "Player.h"
#include "PowerPlant.h"
#include "House.h"
#include "ResourceMarket.h"
#include "Map.h"
#include <sstream>
class IOFile
{
public:
	IOFile();
	~IOFile();
	//save map inputs to map.txt
	//Map
	static void saveMap();
	static void readMapInput(string areaColor);
	static void addEdges();
	
	//Player
	static void savePlayer(vector<Player*> player_vector);
	static std::vector<Player *> loadPlayer();
	static void savePlayerOrder(vector<Player*> player_vector);

	//PowerPlant
	static void savePowerplants(vector<PowerPlant> * ppv);//1 file with writing in game or not True False
	static std::vector<PowerPlant> * loadPowerplants();
	static int splitString(string variable);

	//House
	static void savePlayerHouse(vector<House> house_vector, vector<Player*> player_vector);
	static void loadPlayerHouse(vector<Player*> player_vector);
	
	//Resources
	static void saveResourceMarket(ResourceMarket * resourceMarket);
	static ResourceMarket * loadResourceMarket();
	
};


