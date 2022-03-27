#include <iostream>
#include <random>

#include "../include/model.h"
#include "../include/view.h"

Coord Game::get_rand_coord(){
    Coord target = view::get("text")->get_max_coord();

    std::uniform_int_distribution<int> distrib_x (1, target.x);
    std::uniform_int_distribution<int> distrib_y (1, target.y);

    target.x = distrib_x(Game::gen);
    target.y = distrib_y(Game::gen);

    return target;
}
