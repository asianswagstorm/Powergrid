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

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

tuple<int, string, int> * Map::index_cityName_area = new tuple<int, string, int>[Map::getMapSize()];

//Connected graph of map
adjacency_list_t * Map::map = new adjacency_list_t(Map::getMapSize());

//Initialize values of the Map
Map::Map()
{
	//Read map 
	IOFile::readMapInput();
	
	addEdge(0, 1, 3);
	addEdge(0, 2, 12);
	addEdge(0, 3, 9);
	addEdge(1, 2, 13);
	addEdge(1, 7, 24); //to test single map area comment this out 
	addEdge(2, 7, 23); //to test single map area comment this out 
	addEdge(2, 8, 8); //to test single map area comment this out 
	addEdge(2, 4, 24);
	addEdge(2, 3, 12);
	addEdge(3, 4, 9);
	addEdge(3, 21, 17); //to test single map area comment this out 
	addEdge(3, 23, 18); //to test single map area comment this out 
	addEdge(4, 5, 0);
	addEdge(4, 6, 14);
	addEdge(4, 23, 18); 
	addEdge(5, 8, 21);
	addEdge(5, 14, 16);
	addEdge(5, 13, 13);
	addEdge(6, 23, 8);
	addEdge(6, 14, 5);
	addEdge(6, 24, 13);
	addEdge(7, 8, 27);
	addEdge(7, 9, 14);
	addEdge(7, 10, 9);
	addEdge(8, 9, 18);
	addEdge(8, 13, 28);
	addEdge(9, 10, 9);
	addEdge(9, 11, 9);
	addEdge(9, 12, 15);
	addEdge(9, 13, 27);
	addEdge(10, 11, 3);
	addEdge(11, 12, 14);
	addEdge(12, 13, 18);
	addEdge(13, 14, 16);
	addEdge(13, 15, 15);
	addEdge(13, 16, 16);
	addEdge(13, 17, 21);
	addEdge(14, 15, 8);
	addEdge(14, 18, 12);
	addEdge(14, 25, 6);
	addEdge(14, 24, 8);
	addEdge(15, 16, 3);
	addEdge(15, 18, 14);
	addEdge(16, 17, 5);
	addEdge(16, 19, 12);
	addEdge(16, 18, 12);
	addEdge(17, 19, 8);
	addEdge(18, 25, 7);
	addEdge(18, 20, 6);
	addEdge(18, 19, 7);
	addEdge(19, 20, 11);
	addEdge(19, 39, 16);
	addEdge(20, 37, 3);
	addEdge(20, 39, 9);
	addEdge(21, 22, 6);
	addEdge(21, 23, 6);
	addEdge(22, 23, 5);
	addEdge(22, 24, 12);
	addEdge(22, 28, 15);
	addEdge(23, 24, 8);
	addEdge(24, 25, 10);
	addEdge(24, 26, 7);
	addEdge(24, 28, 7);
	addEdge(25, 26, 12);
	addEdge(25, 37, 12);
	addEdge(26, 27, 6);
	addEdge(26, 36, 15);
	addEdge(26, 30, 7);
	addEdge(26, 28, 4);
	addEdge(27, 37, 5);
	addEdge(28, 29, 7);
	addEdge(28, 30, 6);
	addEdge(29, 30, 7);
	addEdge(29, 32, 8);
	addEdge(30, 34, 6);
	addEdge(30, 36, 7);
	addEdge(31, 32, 3);
	addEdge(32, 33, 0);
	addEdge(33, 34, 3);
	addEdge(34, 35, 5);
	addEdge(35, 36, 3);
	addEdge(36, 37, 7);
	addEdge(36, 38, 7);
	addEdge(37, 38, 7);
	addEdge(38, 39, 0);
	addEdge(39, 40, 4);
	addEdge(40, 41, 4);
	
}

Map::~Map()
{

}
int Map::getMapSize() {
	return mapSize;
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
		weight_t dist = vertex_queue.begin()->first;
		vertex_t node_index = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting the node_index
		const std::vector<neighbor> &neighbors = adjacency_list[node_index];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_node = dist + weight;
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



