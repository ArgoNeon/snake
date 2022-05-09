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
bool final = false;

void signhandler(int sign) {
    	final = true;
}

void TView::cleanscreen() {
    	printf("\e[H\e[J");
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
	ioctl(1, TIOCSWINSZ, &window);
	
	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLUE);
	tile = {' ', ' '};
	wline(0, 0, windSize.second/2);
	hline(0, 0, windSize.first);
	hline(windSize.second/2, 0, windSize.first);
	wline(0, windSize.first, windSize.second/2);
	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLACK);
	fflush(stdout);
}

void TView::drawSnake(const Control::Snake &snake) {
	setcolor(FOREGROUND_COL_MAGENTA, BACKGROUND_COL_BLACK);
	
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

	setcolor(FOREGROUND_COL_CYAN, BACKGROUND_COL_BLACK);

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
		fflush(stdout);
	}
	

}

void TView::draw() {
	cleanscreen();
	drawBox();
	//drawSnake();
	fflush(stdout);
	usleep(500);	
}

void TView::MainLoop() {
	const int tmslp = 500;
	int p;
	char c;
	
	while (!final) {
		struct pollfd arr = {0, POLLIN};
    		p = poll(&arr, 1, tmslp);
		draw();
		
    		if (p == 1) {
        		scanf("%c", &c);

        		if (c == 'q') {
            			break;
        		}
			
			if (c == 033) {
				break;
			}
		}
    	}
	cleanscreen();
	gotoxy(1, 1);
	setcolor(FOREGROUND_COL_RED, BACKGROUND_COL_BLACK);
	printf("YOU DIED...\n");
	fflush(stdout);
}

void TView::drawRabbit(const coord_t &rabbit) {
	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLACK);

  	gotoxy(rabbit.first, rabbit.second);
  	printf("R");
	fflush(stdout);
}

TView::TView() {
	struct termios s;
	tcgetattr(0,&s);
	old_term = s;
	cfmakeraw(&s);
	s.c_lflag |= ISIG;
	tcsetattr(0,TCSANOW,&s);
	signal(SIGINT, signhandler);
}

/*TView::~TView() {
	tcsetattr(0,TCSANOW,&old_term);
}
*/

void TView::run() {
	printf("Nice\n");
}

} //graphicInterface
