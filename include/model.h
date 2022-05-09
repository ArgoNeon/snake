#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <random>
#include <list>
#include <chrono>

#include "human.h"

namespace gameModel {
using coord_t = std::pair<int, int>;
class Game {
private:
	const int numRabbits = 13;
	const int defSnakeLen = 5;
	std::mt19937 gen {static_cast<long unsigned int> (std::chrono::system_clock::now ().time_since_epoch ().count ())};
	std::list<coord_t> rabbits;
	std::list<Control::Snake *> snakes;

	coord_t getNewRandomCoordinate();
	void snakeStep(Control::Snake &s);
	void drawScreen();
	int controller();
	bool checkSnakeCrash();
	bool checkWin();

public:
	Game();
	void addPlayer(Control::Player &p);
	void addBot(Control::Bot &p);
	~Game();
};
} //namespace gameModel

#endif// GAME_MODEL_H
