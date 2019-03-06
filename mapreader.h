//============================================================================
// Name        : mapreader.h
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : reads a map and validate it
//============================================================================
#ifndef MAPREADER_H_
#define MAPREADER_H_

using namespace std;


class mapreader {

public:
	int Index;
	string CityName;
	string Area;


public:
	int setIndex(int index){
		Index = index;
	}
	string setCityName( string cityName){
			CityName = cityName;
	}
	string setArea( string area){
		Area = area;
	}

};







