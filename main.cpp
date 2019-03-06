#include <iostream>
#include <vector>
#include "PowerPlant.h"
#include <cstdlib>
#include <algorithm> // std::random_shuffle
#include <ctime> // std::time()
#include "SummaryCard.h"
#include "Map.h"
#include "Area.h"
#include "IOFile.h"
#include "mapreader.h"

#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <list>

using std::cout;
using namespace ::std;

int main() {
	int option;
	

	do {
		std::cout << "Pick something " << std::endl;
		std::cin >> option;
		if (option == 1) {
			vector<int> areas = { 0,2,3,5 }; //To test areas in use, enter the areas here //0,2,3,5 , test 1 area 0,0,0
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
			std::cout << "Map Created " << std::endl;
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

			std::cout << "Distance from " << start_node << " to " << end_node << ": " << min_distance[end_node] << std::endl;
			std::list<vertex_t> path = test.DijkstraGetShortestPathTo(end_node, previous); //list that will contain the paths taken
			std::cout << "Path : ";
			std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
			std::cout << std::endl;

			std::cout << "Starting City: " + test.getCityName(start_node) + " Ending City: " + test.getCityName(end_node) << std::endl;
		}
		if (option == 2) {
			mapreader map;

			map.readMap();
		}

		if (option == 5) {
			//a pool are filled with cards
			PowerPlant::pool();

			//create 6 summary cards, they do nothing than just print the rules
			SummaryCard *sc1 = new SummaryCard();
			SummaryCard *sc2 = new SummaryCard();
			SummaryCard *sc3 = new SummaryCard();
			SummaryCard *sc4 = new SummaryCard();
			SummaryCard *sc5 = new SummaryCard();
			SummaryCard *sc6 = new SummaryCard();

			cout << endl;
			cout << endl;
			cout << endl;
			cout << "==================================================" << endl;
			cout << "==================================================" << endl;
			cout << "==================================================" << endl;
			cout << "===========displaying 6 summary cards=============" << endl;
			cout << "==================================================" << endl;
			cout << "==================================================" << endl;
			cout << "==================================================" << endl;

			sc1->SummaryCardInfo();
			sc2->SummaryCardInfo();
			sc3->SummaryCardInfo();
			sc4->SummaryCardInfo();
			sc5->SummaryCardInfo();
			sc6->SummaryCardInfo();

		}
	} while (option != 0);

		system("pause");
		return 0;
	}