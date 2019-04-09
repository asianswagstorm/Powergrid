#include "ElektroView.h"
#include "Player.h"
#include "IOFile.h"
#include "Game.h"
#include <iostream>
#include <fstream>

ElektroView::ElektroView() {}
ElektroView::~ElektroView() {
	
}
ElektroView::ElektroView(View * view){
	subject = view->subject;
	subject->removeObserver(view);
	subject->registerObserver(this);
	setType(view->getType() + "-Elektro-"); //title to be printed
}

ElektroView::ElektroView(Game * game) : View(game) {}

void ElektroView::Update(){
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "Elektro View" << std::endl << std::endl;
	this->printInfo();
}

void ElektroView::printInfo() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	vector<Player*> players = subject->player_vector;

	std::cout << "---------------Elektro View-----------------" << std::endl << std::endl;
	output << "---------------Elektro View-----------------" << std::endl << std::endl;

	for (unsigned int  i = 0; i < players.size(); i++) {
		std::cout << players[i]->getName() << " has " << players[i]->getElectro() << " elektros." << std::endl; //print to console
		output << players[i]->getName() << " has " << players[i]->getElectro() << " elektros." << std::endl; // print to game_stats
	}
	std::cout << std::endl;
	output << std::endl;
}