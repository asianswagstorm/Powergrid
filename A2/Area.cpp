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

int Area::getAreaNumber(string area_color) {
	if (area_color == "purple") {
		return 0; //purple area
	}
	if (area_color == "blue") {
		return 1; //blue area
	}
	if (area_color == "red") {
		return 2; //red area
	}
	if (area_color == "yellow") {
		return 3; //yellow area
	}
	if (area_color == "brown") {
		return 4; //brown area
	}
	if (area_color == "green") {
		return 5; //green area
	}

	else return -1;
	
}

void Area::setGameAreas(vector<int> &colors) {
	std::cout << "Area Played: {";
	for (int i : colors) {
		Area::area_is_played[i] = true;
		std::cout << i << "," ;
	}
	std::cout << "}" <<std::endl;
	
}

bool Area::areAdjacent(vector<int> &colors) {
	std::sort(colors.begin(), colors.end());
	int size = colors.size(); //areas used

	if (size < 2 || size > 6) { //Game rule: minimum area == 3 for 2 players Assignment Instruction 1 area per player
		return false;
	}

	else if (size == 2) {

		int first = colors[0];
		int second = colors[1];
		
		//impossible games: Areas not adjacent
		if ((first == 0 && second == 4 )
			|| (first == 0 && second == 5 )
			|| (first == 1 && second == 3 )
			|| (first == 1 && second == 4)
			|| (first == 1 && second == 5 )
			|| (first == 2 && second == 4)) {
			return false;
		}
		return true;
	}

	else if (size == 3) {

		int first = colors[0];
		int second = colors[1];
		int third = colors[2];

		//impossible games: Areas not adjacent
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