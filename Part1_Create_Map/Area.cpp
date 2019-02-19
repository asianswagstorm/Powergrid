#include "Area.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 

using namespace std;

using std::vector;
using std::string;

const string Area::PURPLE = "purple"; // 0
const string Area::BLUE = "blue"; // 1
const string Area::RED = "red"; // 2
const string Area::YELLOW = "yellow"; // 3
const string Area::BROWN = "brown"; // 4
const string Area::GREEN = "green"; // 5

bool * Area::area_is_played = new bool[6]{ false,false,false,false,false,false };

Area::Area()
{
}

Area::~Area()
{
}

void Area::setGameAreas(vector<int> &colors) {
	for (int i : colors) {
		Area::area_is_played[i] = true;
	}
}

bool Area::areAdjacent(vector<int> &colors) {

	std::sort(colors.begin(), colors.end());
	int size = colors.size(); //areas used

	if (size < 3 || size > 5) {
		return false;
	}

	else if (size == 3) {

		int first = colors[0];
		int second = colors[1];
		int third = colors[2];

		//impossible games the areas chosen must be adjacent
		if ((first == 0 && second == 1 && third == 4)
			|| (first == 0 && second == 1 && third == 5)
			|| (first == 0 && second == 2 && third == 4)
			|| (first == 0 && second == 4 && third == 5)
			|| (first == 1 && second == 2 && third == 4)
			|| (first == 1 && second == 3 && third == 4)
			|| (first == 1 && second == 3 && third == 5)
			|| (first == 1 && second == 4 && third == 5)) {
			return false;
		}
		return true;
	}
	else if (size == 4) {

		int first = colors[0];
		int second = colors[1];
		int third = colors[2];
		int fourth = colors[3];
		//impossible games the areas chosen must be adjacent
		if ((first == 0 && second == 1 && third == 4 && fourth == 5)
			|| (first == 0 && second == 1 && third == 2 && fourth == 4)
			|| (first == 1 && second == 3 && third == 4 && fourth == 5)) {
			return false;
		}
		return true;
	}

	//else game of 5 areas
	return true;

};