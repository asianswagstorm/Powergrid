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
	void readMap();

	void setIndex(int index);
	void setCityName(string cityName);
	void setArea(string area);

private:
	int index;
	string cityName;
	string area;
	
};