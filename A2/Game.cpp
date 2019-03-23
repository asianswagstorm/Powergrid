#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>

#include "Game.h"
#include "PowerPlant.h"
#include "Map.h"

Game::Game() {
	turn = 0;
}
Game::Game(std::vector<Player*> player_vector, Map *map) {
	turn = 1;
	this->player_vector = player_vector;
}
Game::~Game() {
}

void Game::setTurn(int turn) {
	this -> turn = turn;
}
int Game::getTurn() {
	return turn;
}
/*void Game::playerOrder() {



}*/
void Game::buyPowerPlant() {}