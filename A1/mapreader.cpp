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