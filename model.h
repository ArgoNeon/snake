#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <iostream>
#include <random>
#include <list>

#include "view.h"

class Game {
std::list<Coord> rabbits;
std::mt19937 gen { std::random_device()() };
/*std::random_device rd;
std::mt19937 gen(rd());*/
public:
Coord get_rand_coord();
private:
};

#endif// GAME_MODEL_H
