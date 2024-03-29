#include <iostream>
#include <string>
#include "PowerPlant.h"
#include <ctime> // std::time()
#include <algorithm> // std::random_shuffle
using namespace std;

//Default constructor
PowerPlant::PowerPlant(){
    minPlantCost = 1;
    type = "null";
    typeNum = 1;
    house = 1;

}

//Constructor initializes power plants 
PowerPlant::PowerPlant(int minPlantCost, string type, int typeNum, int house){
    this->minPlantCost = minPlantCost;
    this->type = type; 
    this->typeNum = typeNum;
    this->house = house;

}

//Destructor
PowerPlant::~PowerPlant(){

}

//Mutator function for setting the minimal cost of a power plant
void PowerPlant::setMinPlantCost(int minPlantCost){
    this->minPlantCost = minPlantCost;
}

//Mutator function for setting the type of resources needed to fuel the power plant
void PowerPlant::setType(string type) {
    this->type = type;
}

void PowerPlant::setTypeNum(int typeNum) {
    this->typeNum = typeNum;
}

//Mutator function for setting the number of house/city the power plant can power
void PowerPlant::setHouse(int house){
    this->house = house;
}

//Accessor function to get the minimum bidding cost of the power plant
int PowerPlant::getMinPlantCost(){
    return minPlantCost;
}

//Accessor function to get the type of resources or raw material it needs to power
string PowerPlant::getType(){
    return type;
}


int PowerPlant::getTypeNum() {
    return typeNum;
}

//Accessor function that gets the number of houses the power plant can power
int PowerPlant::getHouse(){
    return house;
}

//Function that prints out the summary of each power plants
 void PowerPlant::printPowerPlantSummary(){
    cout << "*****************************************************************" << endl;
    cout << "This is the power plant and it's stats: " << endl;
    cout << "This is the minimum cost: " << minPlantCost << endl;
    cout << "This is the resource needed: " << type << endl;
    cout << "This is the number of resource needed: " << type << endl;
    cout << "This is the amount of house it can power: " << house << endl;
    cout << "*****************************************************************" << endl;
}

 static vector<PowerPlant*> ppv;

 //static void  printVector(const vector<PowerPlant>&);

 void PowerPlant::pool() {
	 PowerPlant coal4 = PowerPlant(4, "Coal", 2, 1);
	 PowerPlant coal8 = PowerPlant(8, "Coal", 3, 2);
	 PowerPlant coal10 = PowerPlant(10, "Coal", 2, 2);
	 PowerPlant coal15 = PowerPlant(15, "Coal", 2, 3);
	 PowerPlant coal20 = PowerPlant(20, "Coal", 3, 5);
	 PowerPlant coal25 = PowerPlant(25, "Coal", 2, 5);
	 PowerPlant coal31 = PowerPlant(31, "Coal", 3, 6);
	 PowerPlant coal36 = PowerPlant(36, "Coal", 3, 7);
	 PowerPlant coal42 = PowerPlant(42, "Coal", 2, 6);

	 PowerPlant oil3 = PowerPlant(3, "Oil", 2, 1);
	 PowerPlant oil7 = PowerPlant(7, "Oil", 3, 2);
	 PowerPlant oil9 = PowerPlant(9, "Oil", 1, 1);
	 PowerPlant oil16 = PowerPlant(16, "Oil", 2, 3);
	 PowerPlant oil26 = PowerPlant(26, "Oil", 2, 5);
	 PowerPlant oil32 = PowerPlant(32, "Oil", 3, 6);
	 PowerPlant oil35 = PowerPlant(35, "Oil", 1, 5);
	 PowerPlant oil40 = PowerPlant(40, "Oil", 2, 6);

	 PowerPlant hybrid5(5, "Hybrid", 2, 1);
	 PowerPlant hybrid12(12, "Hybrid", 2, 2);
	 PowerPlant hybrid21(21, "Hybrid", 2, 4);
	 PowerPlant hybrid29(29, "Hybrid", 1, 4);
	 PowerPlant hybrid46(46, "Hybrid", 3, 7);

	 PowerPlant garbage6(6, "Garbage", 1, 1);
	 PowerPlant garbage14(14, "Garbage", 2, 2);
	 PowerPlant garbage19(19, "Garbage", 2, 3);
	 PowerPlant garbage24(24, "Garbage", 2, 4);
	 PowerPlant garbage30(30, "Garbage", 3, 6);
	 PowerPlant garbage38(38, "Garbage", 3, 7);

	 PowerPlant uranium11(11, "Uranium", 1, 1);
	 PowerPlant uranium17(17, "Uranium", 1, 2);
	 PowerPlant uranium23(23, "Uranium", 1, 3);
	 PowerPlant uranium28(28, "Uranium", 1, 4);
	 PowerPlant uranium34(34, "Uranium", 1, 5);
	 PowerPlant uranium39(39, "Uranium", 1, 6);

	 PowerPlant eco13(13, "Eco", 0, 1);
	 PowerPlant eco18(18, "Eco", 0, 2);
	 PowerPlant eco22(22, "Eco", 0, 2);
	 PowerPlant eco27(27, "Eco", 0, 3);
	 PowerPlant eco33(33, "Eco", 0, 4);
	 PowerPlant eco37(37, "Eco", 0, 4);
	 PowerPlant eco44(44, "Eco", 0, 5);
	 PowerPlant eco50(50, "Eco", 0, 6);

	 PowerPlant step3(-1, "Step 3", -1, -1);

	 //PowerPlant Start
	 ppv.push_back(&oil3);
	 ppv.push_back(&coal4);
	 ppv.push_back(&hybrid5);
	 ppv.push_back(&garbage6);
	 ppv.push_back(&oil7);
	 ppv.push_back(&coal8);
	 ppv.push_back(&oil9);
	 ppv.push_back(&coal10);
	 ppv.push_back(&eco13);

	 //PowerPlant deck
	 ppv.push_back(&coal15);
	 ppv.push_back(&coal20);
	 ppv.push_back(&coal25);
	 ppv.push_back(&coal31);
	 ppv.push_back(&coal36);
	 ppv.push_back(&coal42);

	 ppv.push_back(&oil16);
	 ppv.push_back(&oil26);
	 ppv.push_back(&oil32);
	 ppv.push_back(&oil35);
	 ppv.push_back(&oil40);


	 ppv.push_back(&hybrid12);
	 ppv.push_back(&hybrid21);
	 ppv.push_back(&hybrid29);
	 ppv.push_back(&hybrid46);

	 ppv.push_back(&garbage14);
	 ppv.push_back(&garbage19);
	 ppv.push_back(&garbage24);
	 ppv.push_back(&garbage30);
	 ppv.push_back(&garbage38);

	 ppv.push_back(&uranium11);
	 ppv.push_back(&uranium17);
	 ppv.push_back(&uranium23);
	 ppv.push_back(&uranium28);
	 ppv.push_back(&uranium34);
	 ppv.push_back(&uranium39);

	 ppv.push_back(&eco18);
	 ppv.push_back(&eco22);
	 ppv.push_back(&eco27);
	 ppv.push_back(&eco33);
	 ppv.push_back(&eco37);
	 ppv.push_back(&eco44);
	 ppv.push_back(&eco50);

	 //Step 3 card at the end
	 ppv.push_back(&step3);

	 for (int i = 0; i < ppv.size(); i++) {
		 ppv[i]->printPowerPlantSummary();
	 }


	 cout << "==================================================" << endl;
	 cout << "==================================================" << endl;
	 cout << "==================================================" << endl;
	 cout << "===========after finishing shuffle================" << endl;
	 cout << "==================================================" << endl;
	 cout << "==================================================" << endl;
	 cout << "==================================================" << endl;

	 //Used to make random_shuffle random
//See:https://stackoverflow.com/questions/13459953/random-shuffle-not-really-random
	 std::srand(std::time(0));

	 //Randomly shuffle the cards
	 //from index 9 (PowerPlant 13) to end-1 (excluding step 3)
	 random_shuffle(ppv.begin() + 9, ppv.end() - 1);

	 for (int i = 0; i < ppv.size(); i++) {
		 ppv[i]->printPowerPlantSummary();
	 }

 };