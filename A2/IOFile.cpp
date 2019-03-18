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
void IOFile::readMapInput() {
	ifstream mapInputs;
	mapInputs.open("full_map_Inputs.txt"); 

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

	while (getline(edgeInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		
		getline(ss, index1_s, ',');
		index1 = stoi(index1_s); //Convert string to int
		getline(ss, index2_s, ',');
		index2 = stoi(index2_s); //Convert string to int
		getline(ss, weight_s, ',');
		weight = stod(weight_s); //Convert string to double


		/* filter index1 and index2
		*/


		edge_index1.push_back(index1);
		edge_index2.push_back(index2);
		edge_weight.push_back(weight);
	}
	for (unsigned int i = 0; i < edge_index1.size(); i++) {
		Map::addEdge(edge_index1[i], edge_index2[i], edge_weight[i]);
	}
	edgeInputs.close();
}
