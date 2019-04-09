#include "ElektroView.h"
#include "Player.h"
#include "IOFile.h"
#include "Game.h"
#include <iostream>
#include <fstream>

ElektroView::ElektroView() {}
ElektroView::~ElektroView() {
	
}
ElektroView::ElektroView(View * decoratedView) : ViewDecorator(decoratedView){
	subject = decoratedView->subject;
	subject->removeObserver(decoratedView);
	subject->registerObserver(this);
	setType(decoratedView->getType() + "-Elektro-"); //title to be printed
}


void ElektroView::Update(){
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);
	std::cout << "Elektro Info" << std::endl << std::endl;
	this->printInfo();
}

void ElektroView::printInfo() {
	ofstream output;
	output.open("game_statistics.txt", ios::out | ios::app);

	vector<Player*> players = subject->player_vector;
		//IOFile::loadPlayer();
	decoratedView->printInfo();
	
	for (unsigned int  i = 0; i < players.size(); i++) {
		std::cout << players[i]->getName() << " has " << players[i]->getElectro() << " elektros." << std::endl; //print to console
		output << players[i]->getName() << " has " << players[i]->getElectro() << " elektros." << std::endl; // print to game_stats
	}
	std::cout << std::endl;
	output << std::endl;
}