#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <sys/poll.h>
#include <vector>
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

struct termios old_term;
bool final = false;

void signhandler(int sign) {
    	final = true;
}

void tview::cleanscreen() {
    	printf("\e[H\e[J");
}

void tview::gotoxy(int x, int y) {
    	printf("\e[%d;%dH", y, x);
}

void tview::setcolor(int color) {
    	printf("\e[%dm", color);
}

void tview::setcolor(int f_color, int b_color) {
    	printf("\e[%d;%dm", f_color, b_color);
}

void tview::box() {
	int i;
	struct winsize w;

	ioctl(1, TIOCGWINSZ, &w);
	max_coord.x  = w.ws_col;
	max_coord.y  = w.ws_row;

	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLUE);
	gotoxy(1, 1);

	for (i = 1; i < max_coord.x; i++) {
		printf(" ");
	}
	gotoxy(1, max_coord.y);

	for (i = 1; i < max_coord.x; i++) {
		printf(" ");
	}

	for (i = 1; i < max_coord.y; i++) {
		gotoxy(1, i);
		printf(" ");
		gotoxy(max_coord.x, i);
		printf(" ");
	}
}


void tview::draw() {
	cleanscreen();
	box();
	DrawRabbits();
	fflush(stdout);
	usleep(1000);	
}

void tview::MainLoop(){
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

void tview::DrawRabbits() {
  	struct winsize w;
  	ioctl(1, TIOCGWINSZ, &w);
	int i, x, y;
	int n = rand() % 20 + 5;

	setcolor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLACK);

	for (i = 0; i < n; i++) {
  		x = rand() % (w.ws_col - 2) + 2;
  		y = rand() % (w.ws_row - 2) + 2;
  		gotoxy(x, y);
  		printf("R");
	}
}

tview::tview() {
	struct termios s;
	tcgetattr(0,&s);
	old_term = s;
	cfmakeraw(&s);
	s.c_lflag |= ISIG;
	tcsetattr(0,TCSANOW,&s);
	signal(SIGINT, signhandler);
}

tview::~tview() {
	tcsetattr(0,TCSANOW,&old_term);
}

void tview::run() {
	printf("Nice\n");
}

