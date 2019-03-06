#pragma once

#include <iostream>
#include <vector>
#include <string>


using std::string;
using std::tuple;
using std::vector;


class mapreader
{
public:
	mapreader();
	~mapreader();

	int setIndex(int index);
	std::string setCityName(string cityName);
	std::string setArea(string area);
	void readMap();
};


