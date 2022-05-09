#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <random>
#include <algorithm>
#include <iomanip>
#include <set>
#include <utility>
#include <list>
#include <chrono>

#include "human.h"

namespace gameModel {
using coord_t = std::pair<int, int>;
class Game {
private:
	const int numRabbits = 13;
	std::mt19937 gen {static_cast<long unsigned int> (std::chrono::system_clock::now ().time_since_epoch ().count ())};
	std::set<int> rabbits;
	std::set<int> available;
	std::list<Control::Snake *> snakes;

	coord_t getNewRandomCoordinate();
	void snakeStep(Control::Snake &s);
	void drawScreen();
	int controller();
	int numFromCoordinate (const coord_t &coord);
        coord_t coordinateFromNum (int num);
	bool checkSnakeCrash();
        void botsHandler ();
        void setAvailablefields ();
public:
	Game();
	void addPlayer(Control::Player &p);
	void addBot(Control::Bot &p);
	~Game() = default;
};
} //namespace gameModel

#endif// GAME_MODEL_H

