#include <iostream>
#include <random>

#include "../include/model.h"
#include "../include/view.h"

namespace gameModel {

Game::Game() {
	auto v = graphicInterface::View::get();

        v->draw = std::bind (&Game::drawScreen, this);
        v->move = std::bind (&Game::controller, this);
        //v->botsHandler = std::bind (&Game::botsHandler, this);
        v->resizeHandler = std::bind (&Game::setAvailableTiles, this);	
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

void Game::setAvailableTiles () {
        available.clear();
        rabbits.clear();

        auto windSize = graphicInterface::View::get ()->getWindowSize ();
        auto tileSize = (windSize.first - 2) * (windSize.second - 2);

        std::generate_n (std::inserter (available, available.end ()), tileSize - 1, [n = 0] () mutable { return n++; });

        for (auto s : snakes)
            std::for_each (s->body.begin (), s->body.end (), [this] (auto snakeTile) { available.erase (numFromCoordinate (snakeTile)); });

        for (int i = 0; i < numRabbits; i++) {
            if (!available.size ())
                break;
            auto rab = numFromCoordinate(getNewRandomCoordinate ());
            rabbits.insert (rab);
            available.erase (rab);
        }
}

void Game::snakeStep (Control::Snake &s) {
        s.prevDirection = s.direction;
        auto head = s.body.front();
        bool noEat = true;

        coord_t nextHead;

        switch (s.direction) {
           	case Control::Snake::dir::UP: nextHead = {head.first, head.second - 1}; break;
            	case Control::Snake::dir::DOWN: nextHead = {head.first, head.second + 1}; break;
           	case Control::Snake::dir::LEFT: nextHead = {head.first - 1, head.second}; break;
            	case Control::Snake::dir::RIGHT: nextHead = {head.first + 1, head.second}; break;
        }

        s.body.push_front (nextHead);
        available.erase (numFromCoordinate (nextHead));

        for (auto iter = rabbits.begin(); iter != rabbits.end(); ++iter) {
            	if (coordinateFromNum (*iter) == nextHead) {
                	rabbits.erase (iter);
                	noEat = false;

                	if (available.size ()) {
				auto nextRabbit = numFromCoordinate(getNewRandomCoordinate());
				rabbits.insert (nextRabbit);
                    		available.erase (nextRabbit);
                	}
                break;
            	}
        }

        if (noEat) {							//если съел зайца, то конец не удаляем
           	 available.insert (numFromCoordinate (s.body.back()));
           	 s.body.pop_back ();
        }
}

bool Game::checkSnakeCrash() {
	bool death = false;
        auto windSize = graphicInterface::View::get ()->getWindowSize ();

        for (auto iter = snakes.begin(); iter != snakes.end ();) {
            auto prevIter = iter;
            iter++;

            auto head = (*prevIter)->body.front();

            auto deleteSnake = [this, &prevIter] () {
                (*prevIter)->snakeDeath();
                for (auto bodyTile: (*prevIter)->body)
                    available.insert (numFromCoordinate (bodyTile));
                delete *prevIter;
                snakes.erase (prevIter);
            };

            if ((head.first <= 0) || (head.first >= windSize.first - 1)) {
                (*prevIter)->body.pop_front ();
                deleteSnake();
                continue;
            }
            if ((head.second <= 0) || (head.second >= windSize.second - 1)) {
                (*prevIter)->body.pop_front ();
                deleteSnake();
                continue;
            }

            for (auto snakeIter = snakes.begin(); snakeIter != snakes.end(); ++snakeIter) {
                if (snakeIter == prevIter) {
                    for (auto snakeCurIter = std::next ((*prevIter)->body.begin ()); snakeCurIter != (*prevIter)->body.end(); ++snakeCurIter)
                        if (head == (*snakeCurIter)) {
                            death = true;
                            break;
                        }
                }
                else { 
                    for (auto other: (*snakeIter)->body)
                        if (head == other) {
                            death = true;
                            break;
                        }
                }
                if (death) {
                    deleteSnake();
                    break;
                }
            }
        }

        return false;
}

int Game::controller() {
        for (auto &s: snakes)
            	snakeStep (*s);

        checkSnakeCrash();

        if (snakes.empty())
            	return 1;

	return 0;
}

void Game::addPlayer (Control::Player &p) {
	auto size = graphicInterface::View::get()->getWindowSize();
        auto *player = new Control::Player (p);
        player->setSnake ({size.first / 5, size.second / 4 + snakes.size() * 8});

	std::for_each (player->body.begin (), player->body.end (), [this] (auto bodyTile) { available.erase (numFromCoordinate (bodyTile)); });

        player->setButtons();
        snakes.push_back (player);
}

void Game::addBot(Control::Bot &p) {

}

} //namespace gameModel

