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
	string indexHolder;

	if (!mapfile) {
		cout << ("Error: text file not found") << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
		std::vector<std::string>  areas;
		std::vector <int> * initial_file_index = new std::vector<int>();
		std::vector <std::string> * initial_file_cityName = new std::vector<std::string>();
		std::vector <int> * initial_file_area = new std::vector<int>();

		while (getline(mapfile, line) && (line != "") && !line.empty()) {
			
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
		}

	if (Area::areAdjacent(*initial_file_area) == true) {
		cout << ("Valid map") << endl;
		IOFile::addEdges(); // load the edges
		Area::setGameAreas(*initial_file_area);
	}
	else {
		cout << ("Not a valid map, areas are not adjacent") << endl;
	}
}
