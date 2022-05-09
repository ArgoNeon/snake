#ifndef GAME_HUMAN_H
#define GAME_HUMAN_H

#include <list>
#include <utility>
#include <vector>
#include <string>

namespace Control {
using coord_t = std::pair<int, int>;

struct Snake {
	enum class man{
            PLAYER,
            BOT
        };

	enum class dir{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
	
	std::string name;
	std::list<coord_t> body;
	dir prevDirection = dir::RIGHT;
	dir direction = dir::RIGHT;
	man manager;

	void setSnake(const coord_t  &start);
	Snake(const man &who) : manager(who) {}
	virtual ~Snake() = 0;
};

class Player: public Snake{
private:
	static inline int numPlayer = 0;
	std::vector<std::string> buttons;

	void buttonHandler (dir direction);
	void initPlayer (const std::initializer_list<std::string> &buttonSet);
public:
	Player (const std::string &standart);
	Player (const std::initializer_list<std::string> &buttonSet);
	void setName (const std::string &Name);
        ~Player() override = default;
};

class Bot: public Snake {

	virtual ~Bot() = 0;
};

class StupidBot: public Bot{

	~StupidBot() override = default;
};

class CleverBot: public Bot{

	~CleverBot() override = default;
};
} //namespace Control
#endif// GAME_HUMAN_H
