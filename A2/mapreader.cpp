//============================================================================
// Name        : mapreader.h
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : reads a map and validate it
//============================================================================
//#ifndef MAPREADER_H_
#include "mapreader.h"
#include "Area.h"
#include "IOFile.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>
#include <vector>

#define MAPREADER_H_

using namespace std;

mapreader::mapreader() {
	this->index = 0;
	this->cityName = "";
	this->area = "";
}
mapreader::~mapreader() {
}

void mapreader::setIndex(int index) {
	this->index = index;
}

void mapreader::setCityName(string cityName) {
	this->cityName = cityName;
}

void mapreader::setArea(string area) {
	this->area = area;
}

void mapreader::readMap(string mapFileName) {
	ifstream mapfile(mapFileName+".txt");
	int index;
	string cityName;
	string area;
	string line;
	int lineCounter = 0;
	string indexHolder;

	if (!mapfile) {
		cout << ("Error: text file not found") << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
		std::vector<std::string>  areas;
		std::vector <int> * initial_file_index = new vector<int>();
		std::vector <std::string> * initial_file_cityName = new vector<std::string>();
		std::vector <int> * initial_file_area = new vector<int>();

		while (getline(mapfile, line) && (line != "") && !line.empty()) {
			lineCounter++;
			//cout << line << endl;
			std::stringstream ss(line);

			getline(ss, indexHolder, ',');
			index = stoi(indexHolder);
			getline(ss, cityName, ',');
			getline(ss, area, ',');

			areas.push_back(area);

			initial_file_index->push_back(index);
			initial_file_cityName->push_back(cityName);
		
		}

		//clean up vector sort and unique part of <algorithm>
		std::sort(areas.begin(), areas.end());
		areas.erase(std::unique(areas.begin(), areas.end()), areas.end());

		for (int i = 0; i < areas.size(); i++) {
			if (areas[i] == "Purple") {
				initial_file_area->push_back(0);
			}

			else if (areas[i] == "Blue") {
				initial_file_area->push_back(1);
			}

			else if (areas[i] == "Red") {
				initial_file_area->push_back(2);
			}

			else if (areas[i] == "Yellow") {
				initial_file_area->push_back(3);
			}

			else if (areas[i] == "Brown") {
				initial_file_area->push_back(4);
			}

			else if (areas[i] == "Green") {
				initial_file_area->push_back(5);
			}

			else cout << ("Map Area not recognized") << endl;
			
			cout << areas[i] << endl;
		}


	if (Area::areAdjacent(*initial_file_area) == true) {
		cout << ("Valid map") << endl;
		IOFile::addEdges(); // load the edges
	}
	else {
		cout << ("Not a valid map, areas are not adjacent") << endl;
	}
}

/*
void Board::loadMap(string areaText, string mapText) {

	//
	//Load map section
	//
	ifstream inputMap(mapText);

	vector<vector<string> > * loadMap = new vector<vector<string> >(42);

	string skip;

	//Fills up loadMap vector from map.txt
	while (!inputMap.eof()) {

		inputMap >> skip;

		//splits the string with the delimiter ','
		vector<string> internal;
		stringstream ss(skip); // Turn the string into a stream.
		string tok;
		//put string into vector
		while (getline(ss, tok, ',')) {
			internal.push_back(tok);
		}

		//get the index
		int index = stoi(internal[0]);

		//no player
		if (internal.size() == 1) {

		}
		//1 player
		else if (internal.size() == 2) {

			(*loadMap)[index].push_back(internal[1]);
		}
		//2 player
		else if (internal.size() == 3) {

			(*loadMap)[index].push_back(internal[1]);
			(*loadMap)[index].push_back(internal[2]);
		}
		//3 player
		else if (internal.size() == 4) {

			(*loadMap)[index].push_back(internal[1]);
			(*loadMap)[index].push_back(internal[2]);
			(*loadMap)[index].push_back(internal[3]);
		}
	}


	//Loads the players into map
	mapOfPlayersCity->loadPlayerHouses(*loadMap);

	delete loadMap;
	loadMap = NULL;

	inputMap.close();
}
}
*/