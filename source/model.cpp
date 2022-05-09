#include <iostream>
#include <random>

#include "../include/model.h"
#include "../include/view.h"

namespace gameModel {

Game::Game() {
	auto v = graphicInterface::View::get();
        v->draw = std::bind (&Game::drawScreen, this);
        v->setCoordObjs = std::bind (&Game::controller, this);
        //v->botsHandler = std::bind (&Game::botsHandler, this);
        v->resizeHandler = std::bind (&Game::setAvailablefields, this);	
}


coord_t Game::getNewRandomCoordinate() {
        std::uniform_int_distribution<int> rand (0, available.size () - 1);
        auto rd = rand (gen);
        auto getIt = std::next (available.begin (), rd);
        return coordinateFromNum (*getIt);
}

int Game::numFromCoordinate (const coord_t &coord) {
        auto windSize = graphicInterface::View::get ()->getWindowSize ();

        return (coord.second - 1) * (windSize.first - 2) + coord.first - 1;
}

coord_t Game::coordinateFromNum (int num) {
        auto windSize = graphicInterface::View::get ()->getWindowSize ();

        int x = num % (windSize.first - 2) + 1;
        int y = (num - x + 1) / (windSize.first - 2) + 1;

        return {x, y};
}

void Game::drawScreen () {
        auto v = graphicInterface::View::get();
        v->drawBox();

        std::for_each (rabbits.begin (), rabbits.end (), [this, v] (auto r) { v->drawRabbit(coordinateFromNum (r)); });
        std::for_each (snakes.begin (), snakes.end (), [v] (auto s) { v->drawSnake(*s); });
}

void Game::setAvailablefields () {

}

int Game::controller() {

	return 0;
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

