//============================================================================
// Name        : mapreader.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : reads a map and validate it
//============================================================================

#include "mapreader.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

int main() {
	ifstream mapfile ("mapfile.txt");
	int index;
	string cityName;
	string area;
	string line;
	int lineCounter=0;
	string indexHolder;

	if (!mapfile) {
		        cout << ("Error: text file not found") << endl;
		        system ("pause");
		        exit (EXIT_FAILURE);
		}
	if(mapfile >> index >>','>> cityName >>','>> area){

		while (getline(mapfile, line) && (line != "") && !line.empty()) {
			lineCounter++;
			std::stringstream lineHolder(line);

			getline(lineHolder, indexHolder, ',');
			index= stoi(indexHolder);
			getline(lineHolder, cityName, ',');
			getline(lineHolder, area, ',');

			index.setIndex(index);
			cityName.setCityName(cityName);
			area.setArea(area);
		}
	}
	else{
		cout <<("Not a valid map") << endl;
	}

}




