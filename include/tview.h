#ifndef GAME_TVIEW_H
#define GAME_TVIEW_H
#include <vector>
#include <list>
#include <termios.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "view.h"

namespace graphicInterface{
using coord_t = std::pair<int, int>;
class TView: public View{

public:
	TView();
	~TView() override = default;
	void draw() override;
	void run() override;
	void MainLoop() override;
	void drawRabbit (const coord_t &rabbit) override;
        void drawSnake (const Control::Snake &snake) override;
private:
	struct termios old_term;
	const struct winsize window = {50, 200, 0, 0};
	coord_t windSize {50, 200};
       	std::pair<char, char> tile {' ', ' '};

	void gotoxy(int x, int y);
	void cleanscreen();
	void putc(char c);
	void puts(char * s);
	void setcolor (int color);
	void setcolor (int f_color, int b_color);
	std::pair<int, int> getWindowSize() override;
	void drawBox();
	void hline(int x, int y, int size);
	void wline(int x, int y, int size);
};

void signhandler(int sign);

} //graphicInterface
#endif // GAME_TVIEW_H
