
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
	vector<int> areas = {0,2,3,5}; //To test areas in use, enter the areas here //0,2,3,5
	//Testing if areas are adjacent
	
	if (Area::areAdjacent(areas) == false) {
		std::cout << "Error, areas are not adjacent!" << std::endl;
		system("pause");
		return 1;
	}
	else {
		Area::setGameAreas(areas);
	}

	//create map
	Map test = Map();
	
	//Save map to map.txt
	IOFile::saveMap();
	int start_node;
	int end_node;

	std::cout << "Enter the starting node index: " << std::endl;
	std::cin >> start_node;
	std::cout << "Enter the ending node index: " << std::endl;
	std::cin >> end_node;

	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;
	test.DijkstraComputePaths(start_node, *Map::map, min_distance, previous);

	std::cout << "Distance from "<< start_node << " to " << end_node <<": " << min_distance[end_node] << std::endl;
	std::list<vertex_t> path = test.DijkstraGetShortestPathTo(end_node, previous); //list that will contain the paths taken
	std::cout << "Path : ";
	std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Starting City: " + test.getCityName(start_node) + " Ending City: " + test.getCityName(end_node)  << std::endl;
	
	system("pause");
	return 0;
}