#ifndef GAME_GVIEW_H
#define GAME_GVIEW_H

#include "view.h"

namespace graphicInterface {
using coord_t = std::pair<int, int>;
class GView: public View{
public:
	GView();
	~GView() override = default;
	void drawBox() override;
	void endHandler() override;
        void run() override;
        void drawRabbit (const coord_t &rabbit) override;
        void drawSnake (const Control::Snake &snake) override;
	coord_t getWindowSize() override;
	void eraseButton (const std::string &button) override;
	void addButton (const std::string &button, const std::function<void ()> &handler) override;
private:

};
}  // namespace graphicInterface

#endif // GAME_TVIEW_H
