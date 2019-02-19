#include "IOFile.h"
#include "Map.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;


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
	// Create/open a file
	output.open("map.txt");
	cout << "Saving map..." << endl;

	for (unsigned int i = 0; i < 42; i++) {
			output << i << " , " << Map::getCityName(i) << " , " << Map::getAreaColor(i) << endl;
		
	}

	cout << "Map saved..." << endl;
	output.close();
}
