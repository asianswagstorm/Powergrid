//============================================================================
// Name        : mapreader.h
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : reads a map and validate it
//============================================================================
//#ifndef MAPREADER_H_
#include "mapreader.h"
#include <fstream>
#include <istream>
#include <sstream>
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

void mapreader::readMap() {
	ifstream mapfile("map.txt");
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
	if (mapfile >> index  >> cityName  >> area) {
		cout << ("Valid map") << endl;
		while (getline(mapfile, line) && (line != "") && !line.empty()) {
			lineCounter++;
			cout << line << endl;
			std::stringstream lineHolder(line);

			getline(lineHolder, indexHolder, ',');
			index = stoi(indexHolder);
			getline(lineHolder, cityName, ',');
			getline(lineHolder, area, ',');

			setIndex(index);
			setCityName(cityName);
			setArea(area);
		}
	}
	else {
		cout << ("Not a valid map") << endl;
	}
}

/*
void Board::loadMap(string areaText, string mapText) {

	ifstream inputAreas(areaText);;
	string line;
	inputAreas >> line; //Areas
	inputAreas >> line;

	int i1 = stoi(line); //area1
	inputAreas >> line;
	int i2 = stoi(line); //area2
	inputAreas >> line;
	int i3 = stoi(line); //area3

	Area * a1 = new Area(i1);
	Area * a2 = new Area(i2);
	Area * a3 = new Area(i3);

	//Used for areamanager constructor
	vector<Area> * areas = new vector<Area>();
	areas->push_back(*a1);
	areas->push_back(*a2);
	areas->push_back(*a3);

	inputAreas.close();

	AreaManager * area_manager = new AreaManager(); //do not delete
	area_manager->setGameAreas(*areas); //load areas
	Map *gameMap = new Map(area_manager); //load map

	mapOfPlayersCity = new MapOfPlayersCity(gameMap); //load the areas into the map

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