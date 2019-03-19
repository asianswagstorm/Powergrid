#pragma once

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

using std::string;
using std::tuple;
using std::vector;

typedef int vertex_t;
typedef double weight_t;

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight): target(arg_target), weight(arg_weight) {
	}
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

class Map
{
public:

	Map(string areaColor);
	~Map();

	//City index, cityName, Area ; Indices are found in "PowerGridUsMap_nums.jpg"
	static tuple<int, string, int> * index_cityName_area;

	//Connected graph of map
	static adjacency_list_t * map;

	static int getIndexNumber(int index);
	static string getCityName(int index);
	static int getArea(int index);
	static string getAreaColor(int index);
	static void addIndexNameArea(int index, string name, int area);
	static void addEdge(int index1, int index2, double weight);
	static int getMapSize();
		//Map-graph methods
	std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex,const std::vector<vertex_t> &previous);

	void DijkstraComputePaths(vertex_t source,const adjacency_list_t &adjacency_list,std::vector<weight_t> &min_distance,std::vector<vertex_t> &previous);

private:
	static const int mapSize = 42;
};


