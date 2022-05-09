#include <cstdlib>
#include <cstdio>

#include "include/view.h"
#include "include/model.h"

int main(int argn, char *argv[]) {
	auto screen = graphicInterface::View::get ((argn == 2) ? argv[1] : "text");

	gameModel::Game game;

	Control::Player p1 ("wasd");
	Control::Player p2 ("arrows");

	game.addPlayer(p1);
	
  	//screen -> MainLoop(); 
	screen->drawSnake(p1);
	return 0;
}
