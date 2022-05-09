#include <iostream>
#include <random>

#include "../include/model.h"
#include "../include/view.h"

namespace gameModel {

Game::Game() {
	auto v = graphicInterface::View::get();	
	for (int i = 0; i < numRabbits; i++)
		rabbits.push_back(getNewRandomCoordinate());
}

Game::~Game() {

}


coord_t Game::getNewRandomCoordinate() {
    coord_t target = graphicInterface::View::get()->getWindowSize();
    
    std::uniform_int_distribution<unsigned> distrib_x (1, target.first);
    std::uniform_int_distribution<unsigned> distrib_y (1, target.second);

    target.first = distrib_x(Game::gen);
    target.second = distrib_y(Game::gen);

    return target;
}

void Game::addPlayer (Control::Player &p) {
	auto size = graphicInterface::View::get()->getWindowSize();
        auto *player = new Control::Player (p);
        player->setSnake ({size.first / 5, size.second / 2});
        snakes.push_back (player);
}

void Game::addBot(Control::Bot &p) {

}

} //namespace gameModel

