#include "IOFile.h"
#include "Map.h"
#include "Player.h"
#include "ResourceMarket.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::string;
using std::stoi;
using std::stringstream;
using std::getline;


int size;

//empty constructor
IOFile::IOFile()
{
	
}

//destructor
IOFile::~IOFile()
{
}

//need to filter based on active areas
void IOFile::readMapInput(string areaColor) {
	ifstream mapInputs;
	

	if (areaColor == "purple") {
		mapInputs.open("area_purple.txt");
	}

	if (areaColor == "blue") {
		mapInputs.open("area_blue.txt");
	}

	if (areaColor == "red") {
		mapInputs.open("area_red.txt");
	}

	if (areaColor == "yellow") {
		mapInputs.open("area_yellow.txt");
	}

	if (areaColor == "brown") {
		mapInputs.open("area_brown.txt");
	}

	if (areaColor == "green") {
		mapInputs.open("area_green.txt");
	}

	std::vector <int> initial_file_index;
	std::vector <std::string> initial_file_cityName;
	std::vector <int> initial_file_area;

	int index, area;  std::string cityName, index1, line,area1;
	
	while (getline(mapInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		//mapInputs >> index >> cityName >> area;
		getline(ss, index1, ',');
		index = stoi(index1);
		getline(ss, cityName, ',');
		getline(ss, area1, ',');
		area = stoi(area1);

		initial_file_index.push_back(index);
		initial_file_cityName.push_back(cityName);
		initial_file_area.push_back(area);
	}
	for (unsigned int i = 0; i < initial_file_index.size(); i++) {
		
		Map::addIndexNameArea(initial_file_index[i], initial_file_cityName[i], initial_file_area[i]);
	}
	
	mapInputs.close();

}

//need to filter only the active edges
void IOFile::addEdges() {
	ifstream edgeInputs;
	edgeInputs.open("full_edge_Inputs.txt");
	int index1, index2; double weight; std::string line, index1_s, index2_s, weight_s;
	std::vector <int> edge_index1;
	std::vector <int> edge_index2;
	std::vector <double> edge_weight;

	//check if index1 and index 2 in game
	while (getline(edgeInputs, line) && line != "" && !line.empty()) {
		std::stringstream ss(line);
		
		getline(ss, index1_s, ',');
		index1 = stoi(index1_s); //Convert string to int
		getline(ss, index2_s, ',');
		index2 = stoi(index2_s); //Convert string to int
		getline(ss, weight_s, ',');
		weight = stod(weight_s); //Convert string to double


		// filter index1 and index2
		//87 edges 
		for (int i = 0; i < 87; i++) {
			if (Map::getCityName(index1) != "" && Map::getCityName(index2) != "") {
					edge_index1.push_back(index1);
					edge_index2.push_back(index2);
					edge_weight.push_back(weight);
			
			}
		}

		
	}
	for (unsigned int i = 0; i < edge_index1.size(); i++) {
		Map::addEdge(edge_index1[i], edge_index2[i], edge_weight[i]);
	}
	edgeInputs.close();
}

//saves map to map.txt
void IOFile::saveMap() {
	ofstream output;
	// Create or open a file
	output.open("map.txt");
	std::cout << "Saving map..." << std::endl;

	for (int i = 0; i < Map::getMapSize(); i++) {
		if (Map::getCityName(i) != "")
			output << Map::getIndexNumber(i) << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << std::endl;
		
	}
	
	IOFile::addEdges();
	std::cout << "Map saved..." << std::endl;
	output.close();
}

void IOFile::savePlayer(vector<Player*> player_vector) {
	ofstream output;
	// Create or open a file

	output.open("player.txt");

	for (unsigned int i = 0; i < player_vector.size(); i++) {
	output << "Player Order" << i+1 << ":" << endl;
	output << "Name=" << player_vector[i]->getName() << endl;
	output << "Electro=" << player_vector[i]->getElectro() << endl;
	output << "Houses=" << player_vector[i]->getHouseCounter() << endl; //Optional change to vector ex {0,1,2,3} * create vector print function
	output << "PowerPlants=" << player_vector[i]->getnumOfPowerPlants() << endl; // Optional  change to vector ex {3,4,5} * create vector print function
	output << "Area Color=" << player_vector[i]->getAreaColor() << endl;
	output << "Coal=" << player_vector[i]->getResourceQuantity("Coal") << endl;
	output << "Oil=" << player_vector[i]->getResourceQuantity("Oil") << endl;
	output << "Garbage=" << player_vector[i]->getResourceQuantity("Garbage") << endl;
	output << "Uranium=" << player_vector[i]->getResourceQuantity("Uranium") << endl;
	 
	output << "" << endl;
	std::cout << "Player "<< i+1 <<" saved" << std::endl;
	
	}
	output.close();

}

std::vector<Player *> IOFile::loadPlayer() {
	Player * playerObj;
	std::string line, variable, name, color, variable_value,player;
	int electro, houseCount, powerplantCount, coal,oil,garbage,uranium;
	std::vector<Player *> player_vector;

	ifstream playerInput("player.txt");
	if (playerInput.is_open())
	{
		while (getline(playerInput, line) )
		{
			std::stringstream ss(line);
		
			getline(ss, variable, '=');
			getline(ss, variable_value, '=');

			if (variable == "Name") {
				name = (variable_value);
			}
			else if (variable == "Electro") {
				electro = stoi(variable_value);
			}
			else if (variable == "Houses") {
				houseCount = stoi(variable_value);
			}
			else if (variable == "PowerPlants") {
				powerplantCount = stoi(variable_value);
			} 
			else if (variable == "Area Color") {
				color = (variable_value);
			}

			else if (variable == "Coal") {
				coal = stoi(variable_value);
			}
			else if (variable == "Oil") {
				oil = stoi(variable_value);
			}
			else if (variable == "Garbage") {
				garbage = stoi(variable_value);
			}
			else if (variable == "Uranium") {
				uranium = stoi(variable_value);
			}

			if (line == "" && line.empty()) {
				playerObj = new Player();
				playerObj->setName(name);
				playerObj->setElectro(electro);
				playerObj->getHouse()->setHouse(houseCount);
				playerObj->setnumOfPowerPlants(powerplantCount);
				playerObj->setAreaColor(color);
				playerObj->setResources("Coal",coal);
				playerObj->setResources("Oil", oil);
				playerObj->setResources("Garbage", garbage);
				playerObj->setResources("Uranium", uranium);
				player_vector.push_back(playerObj);
			}
		}
			
			playerInput.close();

	}
	else {std::cout << "Unable to open file" << std::endl; 
	return {};
	}

	std::cout << std::endl<< "Player's Loaded." << std::endl << "Here are your current players : " << std::endl <<std::endl;
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		std::cout << "Player " << i + 1 << ":" << std::endl;
		player_vector[i]->printPlayerInfo();
	}

	return player_vector;
}

void IOFile::savePlayerOrder(vector<Player*> player_vector) {
	ofstream output;
	// Create or open a file
	output.open("playerOrder.txt");
	for (unsigned int i = 0; i < player_vector.size(); i++) {
		output << i + 1 << ":" << endl;
		output << "Name=" << player_vector[i]->getName() << endl;
		output << "Houses=" << player_vector[i]->getHouseCounter() << endl; 
		output << "PowerPlants=" << player_vector[i]->getnumOfPowerPlants() << endl; 
		output << "" << endl;
	}

	std::cout << "Player Order saved" << std::endl;
	output.close();

}
//powerplantCardsShowned ppv
//powerplantCardsOwned  ppvClone

void IOFile::savePowerplants(vector<PowerPlant> * ppv) {
	ofstream output;
	
	output.open("powerplants.txt");

	for (unsigned int i = 0; i < ppv->size(); i++) {
		output << "TypeNum_Bid=" << (*ppv)[i].getTypeNum() << "," <<
			" Type=" << (*ppv)[i].getType() << "," <<
			" Resources_required=" << (*ppv)[i].getMinPlantCost() << "," <<
			" Cities_powered=" << (*ppv)[i].getHouse() << "," <<
			" In_Deck=" << (*ppv)[i].getInDeck() << "," <<
			" Owner=" << (*ppv)[i].getOwner() <<
			std::endl;
	}
	output.close();

}

std::vector<PowerPlant> * IOFile::loadPowerplants() {
	vector<PowerPlant> * ppv = new vector<PowerPlant>(); //all
	vector<PowerPlant> * ppvClone = new vector<PowerPlant>(); //only the ones not owned
	Player * playerObj;
	std::string line, variable1, variable2, variable3, variable4, powerplant_type, player_name;
	int typeNum, resource_required, cities_powered, inDeck;
	bool isInDeck;
	std::vector<Player *> player_vector;

	ifstream powerplantInput("powerplants.txt");
	if (powerplantInput.is_open())
	{
		
		while (getline(powerplantInput, line) && (line != "") && !line.empty()) {
			std::stringstream ss(line);
			
			getline(ss, variable1, ','); //type num is here (done)
			typeNum = IOFile::splitString(variable1);//done

			getline(ss, powerplant_type, ','); 
			powerplant_type = powerplant_type.substr(6, powerplant_type.length()); //done

			getline(ss, variable2, ','); // resource required
			resource_required = IOFile::splitString(variable2); //done

			getline(ss, variable3, ','); //cities powered (done)
			cities_powered = IOFile::splitString(variable3); // done 
			
			getline(ss, variable4, ',');
			variable4 = variable4.substr((variable4.size() - 1), variable4.size());
			inDeck = stoi(variable4); // done
			if (inDeck == 0) {
				isInDeck = false;
			}
			if (inDeck == 1) {
				isInDeck = true;
			}

			getline(ss, player_name, ','); // player_name is here
			player_name = player_name.substr(7, player_name.length()); //done
			//std::cout << typeNum << " " << powerplant_type << " " << resource_required << " " << cities_powered << " " << isInDeck << " " << player_name << std::endl;
			PowerPlant powerplant_Obj = PowerPlant(typeNum, powerplant_type, resource_required, cities_powered, isInDeck, player_name);
			ppv->push_back(powerplant_Obj);
			if (isInDeck == true) {
			ppvClone->push_back(powerplant_Obj);
			}
		}

		powerplantInput.close();
		return ppvClone;
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		return {};
	}
}

int IOFile::splitString(string variable) {

	variable = variable.substr(variable.size() - 2, variable.size());
	if (variable.substr(0, 1) == "=") {
		variable = variable.substr(variable.size() - 1, variable.size());
	}
	return  stoi(variable); 
}

void IOFile::savePlayerHouse(vector<House> house_vector, vector<Player*> player_vector) {
	
	vector<int> index_vector;
	for (unsigned int i = 0; i < house_vector.size(); i++) {
		index_vector.push_back(house_vector[i].getIndex());
	}
	
	ofstream output;
	// open a file
	output.open("map1.txt");
	std::cout << "Adding Houses..." << std::endl;

	for (int i = 0; i < Map::getMapSize(); i++) {
	
		if (Map::getCityName(i) != ""){
			
			for (unsigned int j = 0; j < index_vector.size(); j++) {
				
				if (Map::getIndexNumber(i) == index_vector[j])
				{
					std::cout << "j is : " << j << std::endl;
					for(unsigned int m = 0; m < player_vector.size() ; m++){
						for (unsigned int k = 0; k < player_vector[m]->Player::getHouse()->HouseHelper::getHouseVector().size(); k++) { //player_vector[j] out of range j =3 
							//something is wrong here else excuted before if. let it be spent too long.
							if (player_vector[m]->Player::getHouse()->HouseHelper::getHouseVector()[k].getisPowered() == true && Map::getIndexNumber(i) == player_vector[m]->Player::getHouse()->HouseHelper::getHouseVector()[k].getIndex()) {
								output << index_vector[j] << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << ", " << player_vector[m]->getName() << ", Powered" << std::endl;
							}
						else if (player_vector[m]->Player::getHouse()->HouseHelper::getHouseVector()[k].getisPowered() == false && Map::getIndexNumber(i) == player_vector[m]->Player::getHouse()->HouseHelper::getHouseVector()[k].getIndex()) {
								output << index_vector[j] << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << ", " << player_vector[m]->getName() << std::endl;
						}
							}
					}
					i++;
				}
				
				/*if (Map::getIndexNumber(i) == index_vector[j])
				{
					std::cout << "I am Here 4 " << std::endl;
					//remove duplicate
					output << index_vector[j] << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << ", " << player_vector[j]->getName() << std::endl;
					i++;
				}
				*/
			
			}
			std::cout << "I am Here 5 " << std::endl;
			if (i < player_vector.size()*7) {
				std::cout << "I am Here 6 " << std::endl;
				output << Map::getIndexNumber(i) << "," << Map::getCityName(i) << "," << Map::getAreaColor(i) << std::endl;
			}
			
			}
	}
	
	std::cout << "Player Houses saved..." << std::endl;
	output.close();
}

vector<House> IOFile::loadPlayerHouse(vector<Player*> player_vector) {
	//individual house vector
	ifstream mapfile("map.txt");
	int index;
	string cityName;
	string area;
	string line;
	string indexHolder;
	string player;
	
	std::vector<std::string>  areas;
	std::vector <int> * initial_file_index = new std::vector<int>();
	std::vector <std::string> * initial_file_cityName = new std::vector<std::string>();
	std::vector <std::string> * initial_file_Color = new std::vector<std::string>();
	std::vector <string> * initial_file_player = new std::vector<string>();
	std::vector <House>  initial_file_house = std::vector<House>();
	bool isDuplicate = false;
	while (getline(mapfile, line) && (line != "") && !line.empty()) {

		std::stringstream ss(line);

		getline(ss, indexHolder, ',');
		index = stoi(indexHolder);
		getline(ss, cityName, ',');
		getline(ss, area, ',');
		getline(ss, player, ',');

		if(player != ""){ 
		player = player.substr(1, player.size()); // trim the whitespace
		initial_file_player->push_back(player);
		initial_file_index->push_back(index);
		initial_file_cityName->push_back(cityName);
		initial_file_Color->push_back(area);
		House house = House(index, cityName, area);
		initial_file_house.push_back(house);
			for (unsigned int l = 0; l < player_vector.size(); l++) {
				//std::cout << "player_vector[l] : " << player_vector[l]->getName()<< " player is: " << player<< std::endl;
				if (player_vector[l]->getName() == player) {
				//std::cout << "henlo" << std::endl;
				
				//check for duplicates
					for (unsigned int q = 0; q < player_vector[l]->Player::getHouse()->HouseHelper::getHouseVector().size(); q++) {
						if (index == player_vector[l]->Player::getHouse()->HouseHelper::getHouseVector()[q].getIndex())
							isDuplicate = true;
					}
					if(isDuplicate == false){
				player_vector[l]->Player::getHouse()->HouseHelper::addHouse(house);
				player_vector[l]->Player::getHouse()->HouseHelper::setHouse(player_vector[l]->Player::getHouse()->HouseHelper::getHouseVector().size());
					}
					isDuplicate = false; //reset
				//std::cout << std::endl << player_vector[l]->getName() << " house size: " << player_vector[l]->getHouse()->getHouseVector().size();
				}//end if
			}//end for 
		}//endif
		player = "";
	}//end while
	
	for (unsigned int i = 0; i < player_vector.size(); i++) {	
	std::cout << std::endl << player_vector[i]->getName() << " housesize: " << player_vector[i]->getHouse()->getHouseVector().size();
	}
	std::cout << "Houses loaded" <<  std::endl;
	IOFile::savePlayer(player_vector);
	return initial_file_house;
}

void IOFile::saveResourceMarket(ResourceMarket * resourceMarket) {
	ofstream output;
	// open a file
	output.open("resourceMarket.txt");
	std::cout << "Updating Resource Market." << std::endl;

	for (int i = 0; i <= 11; i++) {
		
		output << "Market[" << i << "]: " << std::endl <<
			"Coal=" << resourceMarket->getMarket(i)->getResourceQuantity("Coal") << std::endl << 
			"Oil=" << resourceMarket->getMarket(i)->getResourceQuantity("Oil") << std::endl <<
			"Garbage=" << resourceMarket->getMarket(i)->getResourceQuantity("Garbage") << std::endl <<
			"Uranium=" << resourceMarket->getMarket(i)->getResourceQuantity("Uranium") << std::endl <<
			"Price=" << resourceMarket->getMarket(i)->getResourceCost("Uranium") << endl << endl;

	}
	output.close();

}

//for now doesn't matter

ResourceMarket * IOFile::loadResourceMarket() {
	ResourceMarket * resourceMarket = new ResourceMarket();
	string line, coal= "Coal", oil = "Oil" , garbage = "Garbage",uranium = "Uranium" ,price = "Price", variable, variable_value;
	int coal_value, oil_value, garbage_value, uranium_value, price_value, i = 0;
	ifstream resource_Market_Input("resourceMarket.txt");
	if (resource_Market_Input.is_open())
	{
		while (getline(resource_Market_Input, line))
		{
			std::stringstream ss(line);
			getline(ss, variable, '=');
			getline(ss, variable_value, '=');

			if (variable == coal) {
				coal_value = stoi(variable_value);
			}
			else if (variable == oil) {
				oil_value = stoi(variable_value);
			}
			else if (variable == garbage) {
				garbage_value = stoi(variable_value);
			}
			else if (variable == uranium) {
				uranium_value = stoi(variable_value);
			}
			else if (variable == price) {
				price_value = stoi(variable_value);
			}

			if (line == "" && line.empty()) {
				resourceMarket->getMarket(i)->edit(coal, coal_value, price_value); //edit(type,quantity in market,cost)
				resourceMarket->getMarket(i)->edit(oil, oil_value, price_value);
				resourceMarket->getMarket(i)->edit(garbage, garbage_value, price_value);
				resourceMarket->getMarket(i)->edit(uranium, uranium_value, price_value);
				i++;
			}
		}
		resource_Market_Input.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		
	}
	return resourceMarket;
}