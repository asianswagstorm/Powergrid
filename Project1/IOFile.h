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
	/*TO DO: 
	static void savePowerplantsInGame(); //1 file with writing in game or not True False
	//void savePowerplants();
	//void loadPowerplants(string);

	*/
};


