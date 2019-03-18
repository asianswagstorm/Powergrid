#pragma once
#include "Player.h"
#include <sstream>
class IOFile
{
public:
	IOFile();
	~IOFile();
	//save map inputs to map.txt
	static void saveMap();
	static void readMapInput();
	static void addEdges();

};


