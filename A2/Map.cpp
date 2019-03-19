#include "Map.h"
#include "Area.h"
#include "IOFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <tuple>

using std::get;

//Initialize values of the Map
Map::Map() {

}

Map::Map(string areaColor)
{  
	//Create Map, read inputs from file to reduce code redundancy
	IOFile::readMapInput(areaColor);
	
}

Map::~Map()
{

}

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

tuple<int, string, int> * Map::index_cityName_area = new tuple<int, string, int>[Map::getMapSize()];

//Connected graph of map
adjacency_list_t * Map::map = new adjacency_list_t(Map::getMapSize());

int Map::getMapSize() {
	return mapSize;
}

int Map::getIndexNumber(int index) {
	return get<0>(Map::index_cityName_area[index]);

}
string Map::getCityName(int index) {
	return get<1>(Map::index_cityName_area[index]);
}

int Map::getArea(int index) {
	return get<2>(Map::index_cityName_area[index]);
}

string Map::getAreaColor(int index)
{
	if (index < 7) {
		return "Purple";
	}
	else if (index < 14) {
		return "Blue";
	}
	else if (index < 21) {
		return "Red";
	}
	else if (index < 28) {
		return "Yellow";
	}
	else if (index < 35) {
		return "Brown";
	}
	return "Green";
}

void Map::addEdge(int vertex1, int vertex2, double weight) {

	if (Area::area_is_played[getArea(vertex1)]
		&& Area::area_is_played[getArea(vertex2)]) {
		(*map)[vertex1].push_back(neighbor(vertex2, weight));
		(*map)[vertex2].push_back(neighbor(vertex1, weight));
	}

}

//Adds Index, Name and area to "index_cityName_area"
void Map::addIndexNameArea(int index, string name, int area) {
	index_cityName_area[index] = make_tuple(index, name, area);
}

//Shortest length from initial node to all other vertices
//Output in vector min_distance
void Map::DijkstraComputePaths(vertex_t source,
	const adjacency_list_t &adjacency_list,
	std::vector<weight_t> &min_distance,
	std::vector<vertex_t> &previous)
{
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		weight_t distance = vertex_queue.begin()->first;
		vertex_t node_index = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting the node_index
		const std::vector<neighbor> &neighbors = adjacency_list[node_index];
		// iterator point at the memory addresses (index)
		for (std::vector<neighbor>::const_iterator ptr = neighbors.begin(); ptr != neighbors.end(); ptr++)
		{
			vertex_t v = ptr->target;//vertex being pointed at 
			weight_t weight = ptr->weight;
			weight_t distance_through_node = distance + weight;
			if (distance_through_node < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_node; //setting new min distance 
				previous[v] = node_index;
				vertex_queue.insert(std::make_pair(min_distance[v], v)); //insert new distance into path

			}

		}
	}
}

//Returns path as a list of indices
std::list<vertex_t> Map::DijkstraGetShortestPathTo(
	vertex_t vertex, const std::vector<vertex_t> &previous)
{
	std::list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


void Map::testMap(Map test){
int start_node;
int end_node;
std::cout << "Test if map is connected graph " << std::endl;
std::cout << "Enter the starting node index: " << std::endl;
std::cin >> start_node;
std::cout << "Enter the ending node index: " << std::endl;
std::cin >> end_node;

std::vector<weight_t> min_distance;
std::vector<vertex_t> previous;
test.DijkstraComputePaths(start_node, *Map::map, min_distance, previous);

if (isinf(min_distance[end_node])) {
	std::cout << std::string("ERROR ") << std::endl;
	std::cout << std::string("Index not in path, or Index not located in correct area ") << std::endl;
}
else{
std::cout << std::string("Distance from ") << start_node << std::string(" to ") << end_node << std::string(": ") << min_distance[end_node] << std::endl;
std::list<vertex_t> path = test.DijkstraGetShortestPathTo(end_node, previous); //list that will contain the paths taken
std::cout << std::string("Path : ");
std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
std::cout << std::endl;

std::cout << std::string("Starting City: ") + test.getCityName(start_node) + std::string(" Ending City: ") + test.getCityName(end_node) << std::endl;
}
}