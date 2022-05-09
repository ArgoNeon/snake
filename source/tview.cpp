#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/poll.h>
#include <vector>
#include <list>
#include <sys/ioctl.h>

#include "../include/tview.h"

//Foreground Colors
#define FOREGROUND_COL_BLACK 30
#define FOREGROUND_COL_RED 31
#define FOREGROUND_COL_GREEN 32
#define FOREGROUND_COL_YELLOW 33
#define FOREGROUND_COL_BLUE 34
#define FOREGROUND_COL_MAGENTA 35
#define FOREGROUND_COL_CYAN 36
#define FOREGROUND_COL_WHITE 37

//Background Colors
#define BACKGROUND_COL_BLACK 40
#define BACKGROUND_COL_RED 41
#define BACKGROUND_COL_GREEN 42
#define BACKGROUND_COL_YELLOW 43
#define BACKGROUND_COL_BLUE 44
#define BACKGROUND_COL_MAGENTA 45
#define BACKGROUND_COL_CYAN 46
#define BACKGROUND_COL_WHITE 47

namespace graphicInterface{

void signHandler (int sign) {
	if (sign != SIGINT)
            return;

        TView::interruptHandler();
}

void signChangeWindSizeHandler (int sign) {
        if (sign != SIGWINCH)
            return;

        TView::changeWindSizeHandler ();
}

void TView::endHandler () {
        end = true;
}

void TView::resizer () {
        ioctl (STDOUT_FILENO, TIOCGWINSZ, &window);
        windSize = {window.ws_col / 2, window.ws_row};

        if (!end)
            resizeHandler();
}

void TView::addButton (const std::string &button, const std::function<void ()> &handler) {
	 buttonList.insert ({button, handler});
}

void TView::eraseButton (const std::string &button) {
            auto res = buttonList.find (button);
            if (res != buttonList.end ())
                buttonList.erase (res);
}

TView::TView() {
        struct termios s;
        tcgetattr(0, &old_term);
        cfmakeraw(&s);
        s.c_lflag |= ISIG;
        s.c_cc[VINTR] = 3;
        tcsetattr(0, TCSANOW, &s);

        ioctl (STDOUT_FILENO, TIOCGWINSZ, &window);
        windSize = {window.ws_col / 2, window.ws_row};

        interruptHandler = std::bind (&TView::endHandler, this);
        signal (SIGINT, &graphicInterface::signHandler);
        changeWindSizeHandler = std::bind (&TView::resizer, this);
        signal (SIGWINCH, &graphicInterface::signChangeWindSizeHandler);
}

void TView::gotoxy(int x, int y) {
    	printf("\e[%d;%dH", y, x);
}

void TView::setcolor(int color) {
    	printf("\e[%dm", color);
}

void TView::setcolor(int f_color, int b_color) {
    	printf("\e[%d;%dm", f_color, b_color);
}

void TView::resetcolor(){ 
	printf ("\e[m\e[1;1H"); 
}

std::pair<int, int> TView::getWindowSize () {
       return windSize;
}

void TView::wline(int x, int y, int size) {
	x = x * 2 + 1;
	y++;
	
	gotoxy(x, y);
	for (int i = 0; i < size; i++) {
		printf ("%c%c", tile.first, tile.second);
	}
}

void TView::hline(int x, int y, int size) {
	x = x * 2 + 1;
	y++;

	for (int i = 0; i < size; i++) {
                gotoxy(x, y);
                printf ("%c%c", tile.first, tile.second);
                y++;
        }
}

void TView::drawBox() {
	printf ("\e[1;1H\e[J");	
	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLUE);
	tile = {' ', ' '};
	wline(0, 0, windSize.first - 1);
	hline(0, 0, windSize.second - 1);
	hline(windSize.first - 1, 0, windSize.second - 1);
	wline(0, windSize.second - 1, windSize.first - 1);
	resetcolor();
	fflush(stdout);
}

void TView::drawSnake(const Control::Snake &snake) {
	setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_MAGENTA);
	
	switch(snake.direction) {
		case Control::Snake::dir::RIGHT:
			tile = {' ', '>'};
			break;	
		case Control::Snake::dir::LEFT:
			tile = {'<', ' '};	
			break;
		case Control::Snake::dir::UP:
			tile = {'/', '\\'};	
			break;
		case Control::Snake::dir::DOWN:
			tile = {'\\', '/'};
			break;	
	}

	hline(snake.body.front().first, snake.body.front().second, 1);

	setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_CYAN);

	for (auto iter = ++snake.body.begin(); iter != snake.body.end(); ++iter) {
		auto next = iter;

		if (next->first != iter->first) {
			if (next->first < iter->first) 
				tile = {'<', '<'};
			else
				tile = {'>', '>'};
		} else 
			if (next->second != iter->second) {
				if (next->second < iter->second)
					tile = {'^', '^'};
				else 
					tile = {'v', 'v'};
			}
		hline(next->first, next->second, 1);
	}
	
	resetcolor();
        fflush(stdout);

}

void TView::drawRabbit(const coord_t &rabbit) {
	setcolor(FOREGROUND_COL_BLACK, BACKGROUND_COL_WHITE);
	tile = {' ', ' '};
	hline (rabbit.first, rabbit.second, 1);
  	resetcolor();
	fflush(stdout);
}

void TView::buttonHandler() {
        using namespace std::chrono_literals;
	unsigned char c;
	const int tmslp = 100;
        struct pollfd pollin = {0, POLL_IN, 0};
        std::string request = "";
        auto start = std::chrono::steady_clock::now ();

        while (std::chrono::steady_clock::now () < start + handTime) {
            if (poll (&pollin, 1, tmslp) == 1) { 
                read (0, &c, 1);

                request += c;

                if (auto res = buttonList.find (request); res != buttonList.end ()) {
                    	res->second ();
                    	request = "";
                }

                if (c == 'q') {
			endHandler();
                    	break;
                }
            }
        }
}

    void TView::run () {
        resizeHandler ();
        //int result;
        while (!end) {
            	buttonHandler();
        	/*result = setCoordObjs ();
            	if (result) {
			endHandler ();
               		break;
		 }*/

        	draw();
        }

        /*if (result == 1) {
            	end = false;
        }*/

        //cleanscreen();
	printf ("\e[1;1H\e[J");
        tcsetattr (0, TCSANOW, &old_term);
    }

} //graphicInterface
