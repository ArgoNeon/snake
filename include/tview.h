#ifndef GAME_TVIEW_H
#define GAME_TVIEW_H

#include <poll.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>
#include <list>

#include "view.h"

namespace graphicInterface{
using coord_t = std::pair<int, int>;
class TView: public View{

public:
	TView();
	~TView() override = default;
	void run() override;
	void drawRabbit (const coord_t &rabbit) override;
        void drawSnake (const Control::Snake &snake) override;
	std::pair<int, int> getWindowSize() override;
	void drawBox() override;
	
	static inline std::function<void ()> interruptHandler;
        static inline std::function<void ()> changeWindSizeHandler;

	void addButton (const std::string &button, const std::function<void ()> &handler) override;
        void eraseButton (const std::string &button) override;
private:
	bool end = false;
	struct termios old_term;
	const struct winsize window = {0, 0, 0, 0};
	coord_t windSize {0, 0};
       	std::pair<char, char> tile {' ', ' '};

	std::unordered_map<std::string, std::function<void ()>> buttonList;

	void buttonHandler();
	void resizer();
	void endHandler() override;

	void gotoxy(int x, int y);
	void cleanscreen();
	void putc(char c);
	void puts(char * s);
	void setcolor (int color);
	void setcolor (int f_color, int b_color);
	void resetcolor();
	void hline(int x, int y, int size);
	void wline(int x, int y, int size);
};

} //graphicInterface
#endif // GAME_TVIEW_H
