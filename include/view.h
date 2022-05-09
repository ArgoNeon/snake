#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <iostream>
#include <string>
#include <memory>
#include <string_view>

#include "model.h"

namespace graphicInterface{
using coord_t = std::pair<int, int>;

class View{
public:
	static inline const std::string_view textView = "text";
        static inline const std::string_view graphView = "graph";
	static inline std::shared_ptr<View> obj = nullptr;
        static std::shared_ptr<View> get (const std::string &type = "");

	virtual coord_t getWindowSize() = 0;
	virtual void MainLoop() = 0;
	virtual void draw() = 0;
	virtual void run() = 0;
	virtual void drawRabbit (const coord_t &rabbit) = 0; 
	virtual void drawSnake (const Control::Snake &snake) = 0; 
	virtual ~View() = 0;
private:

};
}  // namespace graphicInterface

#endif // GAME_VIEW_H
