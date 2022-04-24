#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <iostream>
#include <random>
#include <list>

#include "view.h"

class Snake{
public:
	enum class dir{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};
std::list<Coord> body;
dir direction = dir::RIGHT;
};

class Game {
std::list<Coord> rabbits;
std::mt19937 gen { std::random_device()() };
public:
Coord get_rand_coord();
private:
};

#endif// GAME_MODEL_H
