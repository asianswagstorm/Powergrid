#include "IOFile.h"
#include "Map.h"

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
	cout << "Saving map..." << endl;
	
	for (unsigned int i = 0; i < Map::getMapSize(); i++) {
		if(Map::getCityName(i) != "")
		 output << i << " , " << Map::getCityName(i) << " , " << Map::getAreaColor(i) << endl;
		else 
		 output << endl;
	}

	cout << "Map saved..." << endl;
	output.close();
}

void IOFile::readMapInput() {
	ifstream mapInputs;
	mapInputs.open("map_Inputs.txt");

	std::vector <int> initial_file_index;
	std::vector <std::string> initial_file_cityName;
	std::vector <int> initial_file_area;

	int index; int area;  std::string cityName, index1, line,area1;
	
	while (getline(mapInputs, line)) {
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
