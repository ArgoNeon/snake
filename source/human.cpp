#include <queue>
#include <algorithm>

#include "../include/human.h"
#include "../include/model.h"
#include "../include/view.h"

namespace Control {

	void Player::buttonHandler(dir direct) {
		switch (direct) {
                case Snake::dir::UP:
			if (prevDirection != dir::DOWN)
				direction = dir::UP;
			break;
                case Snake::dir::DOWN:
			if (prevDirection != dir::UP)
				direction = dir::DOWN;
			break;
                case Snake::dir::LEFT:
			if (prevDirection != dir::RIGHT)
				direction = dir::LEFT;
			break;
                case Snake::dir::RIGHT:
			if (prevDirection != dir::LEFT)
				direction = dir::RIGHT;
			break;
		}
	}

	void Snake::setSnake(const coord_t  &start) {
                for (int i = 0; i < 5; i++) {
                        body.push_back({start.first - i, start.second});
                }
        }

	size_t Snake::getLength() { 
		return body.size ();
	}
	
	void Player::snakeDeath() {
        	auto v = graphicInterface::View::get();

        	for (auto but: buttons)
            		v->eraseButton (but);
   	}
	
	void Player::initPlayer (const std::initializer_list<std::string> &buttonSet) {
		name = "Player_" + std::to_string(++numPlayer);

       		if (buttonSet.size () != 4)
            		throw std::logic_error ("Wrong quantity of buttons");

        	std::for_each (buttonSet.begin (), buttonSet.end (), [this] (auto but) { buttons.push_back (but);});
	}

	Player::Player (const std::initializer_list<std::string> &buttonSet) : Snake(man::PLAYER) {
	       	initPlayer (buttonSet);
	}


	Player::Player (const std::string &standart) : Snake(man::PLAYER) {

			if (standart == "arrows") {
				initPlayer ({"\e[A", "\e[D", "\e[B", "\e[C"});
            			return;
			}
			
		       	if (standart == "wasd") {
				initPlayer ({"w", "a", "s", "d"});
				return;
			}

			throw std::invalid_argument ("Strange combination");
	}

	void Player::setButtons() {
		auto v = graphicInterface::View::get ();

        	std::for_each (buttons.begin(), buttons.end (), [this, v, direct = 0] (auto but) mutable { v->addButton (but, std::bind (&Player::buttonHandler, this, static_cast<dir> (direct++))); });
	}

	Snake::~Snake() {}
}  // namespace Control

