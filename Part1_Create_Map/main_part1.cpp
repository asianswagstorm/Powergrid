
#include "Map.h"
#include "Area.h"
#include "IOFile.h"

#include <iostream>
#include <vector>
#include <string>
#include <list>

using std::cout;

int main()
{
	vector<int> areas = {0,2,3,5 }; //To test areas in use, enter the areas here
	Area::setGameAreas(areas);
	//Testing if areas are adjacent
	
	if (Area::areAdjacent(areas) == false) {
		std::cout << "Error, areas are not adjacent!" << std::endl;
		system("pause");
		return 0;
	}

	//create map
	Map test = Map();
	
	//Save map to map.txt
	IOFile::saveMap();

	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;
	test.DijkstraComputePaths(0, *Map::map, min_distance, previous);

	std::cout << "Distance from 0 to 41: " << min_distance[41] << std::endl;
	std::list<vertex_t> path = test.DijkstraGetShortestPathTo(41, previous); //list that will contain the paths taken
	std::cout << "Path : ";
	std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Starting City: " + test.getCityName(0) + " Ending City: " + test.getCityName(41)  << std::endl;
	
	system("pause");
	return 0;
}