#ifndef GAME_TVIEW_H
#define GAME_TVIEW_H
#include <vector>

#include "view.h"

class tview: public view{

public:
	tview();
	~tview();
	void draw() override;
	void run() override;
	void MainLoop() override;
private:
	void gotoxy(int x, int y);
	void cleanscreen();
	void putc(char c);
	void puts(char * s);
	void setcolor (int color);
	void setcolor (int f_color, int b_color);
	void box();
	void DrawRabbits();
	void hline();
	void wline();
};

void signhandler(int sign);

#endif // GAME_TVIEW_H
