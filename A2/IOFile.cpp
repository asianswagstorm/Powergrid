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

/*//Saves player houses
	for (unsigned int i = 0; i < player_houses->size(); i++) {
		if ((*player_houses)[i].size() == 0) {
			outputMap << i << endl;
		}
		else if ((*player_houses)[i].size() == 1) {
			outputMap << i << "," << (*player_houses)[i][0] << endl;
		}
		else if ((*player_houses)[i].size() == 2) {
			outputMap << i << "," << (*player_houses)[i][0] << "," << (*player_houses)[i][1] << endl;
		}
		else if ((*player_houses)[i].size() == 3) {
			outputMap << i << "," << (*player_houses)[i][0] << "," << (*player_houses)[i][1] << "," << (*player_houses)[i][2] << endl;
		}
	}

*/

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