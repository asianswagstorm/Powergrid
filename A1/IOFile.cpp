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

//empty constructor
IOFile::IOFile()
{
}

//destructor
IOFile::~IOFile()
{
}

//saves map to map.txt
void IOFile::saveMap() {
	ofstream output;
	// Create or open a file
	output.open("map.txt");
	std::cout << "Saving map..." << std::endl;
	
	for (unsigned int i = 0; i < Map::getMapSize(); i++) {
		if(Map::getCityName(i) != "")
		 output << i << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << std::endl;
		else 
		 output << std::endl;
	}

	std::cout << "Map saved..." << std::endl;
	output.close();
}

void IOFile::readMapInput() {
	ifstream mapInputs;
	mapInputs.open("map_Inputs.txt");

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

void IOFile::addEdges() {
	ifstream edgeInputs;
	edgeInputs.open("edge_Inputs.txt");
	int index1, index2; double weight; std::string line, index1_s, index2_s, weight_s;
	std::vector <int> edge_index1;
	std::vector <int> edge_index2;
	std::vector <double> edge_weight;

	while (getline(edgeInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		
		getline(ss, index1_s, ',');
		index1 = stoi(index1_s); //Convert string to int
		getline(ss, index2_s, ',');
		index2 = stoi(index2_s); //Convert string to int
		getline(ss, weight_s, ',');
		weight = stod(weight_s); //Convert string to double

		edge_index1.push_back(index1);
		edge_index2.push_back(index2);
		edge_weight.push_back(weight);
	}
	for (unsigned int i = 0; i < edge_index1.size(); i++) {
		Map::addEdge(edge_index1[i], edge_index2[i], edge_weight[i]);
	}
	edgeInputs.close();
}

void IOFile::printPlayer(Player &player1, Player &player2){
	ofstream output;
	// Create or open a file
	output.open("player.txt");
	output << "Player1:" << endl;
	output << "Name=" << player1.getName() << endl;
	output << "Electro=" << player1.getElectro() << endl;
	output << "Houses=" << player1.getHouse() << endl;
	output << "Area Color=" << player1.getAreaColor() << endl;
	output << "Coal=" << player1.getCoal() << endl;
	output << "Oil=" << player1.getOil() << endl;
	output << "Garbage=" << player1.getGarbage() << endl;
	output << "Uranium=" << player1.getUranium() << endl;
	output <<  endl;
	std::cout << "Player 1 saved" << std::endl;

	output << "Player2" << endl;
	output << "Name=" << player2.getName() << endl;
	output << "Electro=" << player2.getElectro() << endl;
	output << "Houses=" << player2.getHouse() << endl;
	output << "Color=" << player2.getAreaColor() << endl;
	output << "Coal=" << player2.getCoal() << endl;
	output << "Oil=" << player2.getOil() << endl;
	output << "Garbage=" << player2.getGarbage() << endl;
	output << "Uranium=" << player2.getUranium() << endl;

	std::cout << "Player 2 saved" << std::endl;

	
	output.close();
	}