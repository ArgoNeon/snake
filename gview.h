#ifndef GAME_GVIEW_H
#define GAME_TVIEW_H

#include "view.h"

class gview: public view{
public:
	gview();
	~gview();
	void draw() override;
	void run() override;
	void MainLoop() override;
private:

};

#endif // GAME_TVIEW_H
