#include "IOFile.h"
#include "Map.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;
using std::stringstream;

int size;

//empty constructor
IOFile::IOFile()
{
	
}

//destructor
IOFile::~IOFile()
{
}

//need to filter based on active areas
void IOFile::readMapInput(string areaColor) {
	ifstream mapInputs;
	

	if (areaColor == "purple") {
		mapInputs.open("area_purple.txt");
	}

	if (areaColor == "blue") {
		mapInputs.open("area_blue.txt");
	}

	if (areaColor == "red") {
		mapInputs.open("area_red.txt");
	}

	if (areaColor == "yellow") {
		mapInputs.open("area_yellow.txt");
	}

	if (areaColor == "brown") {
		mapInputs.open("area_brown.txt");
	}

	if (areaColor == "green") {
		mapInputs.open("area_green.txt");
	}

	std::vector <int> initial_file_index;
	std::vector <std::string> initial_file_cityName;
	std::vector <int> initial_file_area;

	int index, area;  std::string cityName, index1, line,area1;
	
	while (getline(mapInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		//mapInputs >> index >> cityName >> area;
		getline(ss, index1, ',');
		index = stoi(index1);
		getline(ss, cityName, ',');
		getline(ss, area1, ',');
		area = stoi(area1);

		initial_file_index.push_back(index);
		initial_file_cityName.push_back(cityName);
		initial_file_area.push_back(area);
	}
	for (unsigned int i = 0; i < initial_file_index.size(); i++) {
		
		Map::addIndexNameArea(initial_file_index[i], initial_file_cityName[i], initial_file_area[i]);
	}
	
	mapInputs.close();

}

//need to filter only the active edges
void IOFile::addEdges() {
	ifstream edgeInputs;
	edgeInputs.open("full_edge_Inputs.txt");
	int index1, index2; double weight; std::string line, index1_s, index2_s, weight_s;
	std::vector <int> edge_index1;
	std::vector <int> edge_index2;
	std::vector <double> edge_weight;

	//check if index1 and index 2 in game
	while (getline(edgeInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		
		getline(ss, index1_s, ',');
		index1 = stoi(index1_s); //Convert string to int
		getline(ss, index2_s, ',');
		index2 = stoi(index2_s); //Convert string to int
		getline(ss, weight_s, ',');
		weight = stod(weight_s); //Convert string to double


		// filter index1 and index2
		//87 edges 
		for (int i = 0; i < 87; i++) {
			if (Map::getCityName(index1) != "" && Map::getCityName(index2) != "") {
					edge_index1.push_back(index1);
					edge_index2.push_back(index2);
					edge_weight.push_back(weight);
			
			}
		}

		
	}
	for (unsigned int i = 0; i < edge_index1.size(); i++) {
		Map::addEdge(edge_index1[i], edge_index2[i], edge_weight[i]);
	}
	edgeInputs.close();
}

//saves map to map.txt
void IOFile::saveMap() {
	ofstream output;
	// Create or open a file
	output.open("map.txt");
	std::cout << "Saving map..." << std::endl;

	for (int i = 0; i < Map::getMapSize(); i++) {
		if (Map::getCityName(i) != "")
			output << Map::getIndexNumber(i) << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << std::endl;
		
	}
	IOFile::addEdges();
	std::cout << "Map saved..." << std::endl;
	output.close();
}

void IOFile::savePlayer(vector<Player*> player_vector) {
	ofstream output;
	// Create or open a file

	output.open("player.txt");

	for (unsigned int i = 0; i < player_vector.size(); i++) {
	output << "Player" << i+1 << ":" << endl;
	output << "Name=" << player_vector[i]->getName() << endl;
	output << "Electro=" << player_vector[i]->getElectro() << endl;
	output << "Houses=" << player_vector[i]->getHouseCounter() << endl; //Optional change to vector ex {0,1,2,3} * create vector print function
	output << "PowerPlants=" << player_vector[i]->getnumOfPowerPlants() << endl; // Optional  change to vector ex {3,4,5} * create vector print function
	output << "Area Color=" << player_vector[i]->getAreaColor() << endl;
	output << "Coal=" << player_vector[i]->getResourceQuantity("Coal") << endl;
	output << "Oil=" << player_vector[i]->getResourceQuantity("Oil") << endl;
	output << "Garbage=" << player_vector[i]->getResourceQuantity("Garbage") << endl;
	output << "Uranium=" << player_vector[i]->getResourceQuantity("Uranium") << endl;
	 
	output << "" << endl;
	std::cout << "Player "<< i+1 <<" saved" << std::endl;
	
	}
	output.close();

}

std::vector<Player *> IOFile::loadPlayer() {
	Player * playerObj;
	std::string line, variable, name, color, variable_value,player;
	int electro, houseCount, powerplantCount, coal,oil,garbage,uranium;
	std::vector<Player *> player_vector;

	ifstream playerInput("player.txt");
	if (playerInput.is_open())
	{
		while (getline(playerInput, line) )
		{
			std::stringstream ss(line);
		
			getline(ss, variable, '=');
			getline(ss, variable_value, '=');

			if (variable == "Name") {
				name = (variable_value);
			}
			else if (variable == "Electro") {
				electro = stoi(variable_value);
			}
			else if (variable == "Houses") {
				houseCount = stoi(variable_value);
			}
			else if (variable == "PowerPlants") {
				powerplantCount = stoi(variable_value);
			} 
			else if (variable == "Area Color") {
				color = (variable_value);
			}

			else if (variable == "Coal") {
				coal = stoi(variable_value);
			}
			else if (variable == "Oil") {
				oil = stoi(variable_value);
			}
			else if (variable == "Garbage") {
				garbage = stoi(variable_value);
			}
			else if (variable == "Uranium") {
				uranium = stoi(variable_value);
			}

			if (line == "" && line.empty()) {
				playerObj = new Player();
				playerObj->setName(name);
				playerObj->setElectro(electro);
				playerObj->getHouse()->setHouse(houseCount);
				playerObj->setnumOfPowerPlants(powerplantCount);
				playerObj->setAreaColor(color);
				playerObj->setResources("Coal",coal);
				playerObj->setResources("Oil", oil);
				playerObj->setResources("Garbage", garbage);
				playerObj->setResources("Uranium", uranium);
				player_vector.push_back(playerObj);
			}
		}
			
			playerInput.close();

	}
	else {std::cout << "Unable to open file" << std::endl; 
	return {};
	}

	std::cout << std::endl<< "Player's Loaded." << std::endl << "Here are your current players : " << std::endl <<std::endl;
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		std::cout << "Player " << i + 1 << ":" << std::endl;
		player_vector[i]->printPlayerInfo();
	}

	return player_vector;
}

void IOFile::savePlayerOrder(vector<Player*> player_vector) {
	ofstream output;
	// Create or open a file
	output.open("playerOrder.txt");
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		output << i + 1 << ":" << endl;
		output << "Name=" << player_vector[i]->getName() << endl;
		output << "Houses=" << player_vector[i]->getHouseCounter() << endl; 
		output << "PowerPlants=" << player_vector[i]->getnumOfPowerPlants() << endl; 
		output << "" << endl;
	}

	std::cout << "Player Order saved" << std::endl;
	output.close();

}

