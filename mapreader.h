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
	int setIndex(int index){
		Index = index;
	}
	string setCityName( string cityName){
			CityName = cityName;
	}
	string setArea( string area){
		Area = area;
	}

	void readMap(){
		ifstream mapfile ("map.txt");
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
				cout << line << endl;
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

private:
	int Index;
	string CityName;
	string Area;


};







