/*#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <random>
#include <list>

class Game{
public:
std::list<Coord> rabbits;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> uid(1, 6);
private:
};

#endif //GAME_GAME_H*/
