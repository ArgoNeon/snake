#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <iostream>
#include <string>
#include <memory>
#include <string_view>
#include <chrono>
#include <functional>

#include "model.h"

namespace graphicInterface{
using coord_t = std::pair<int, int>;
using namespace std::chrono_literals;

class View{
public:
	static inline std::shared_ptr<View> obj = nullptr;
        static std::shared_ptr<View> get (const std::string &type = "");

	virtual coord_t getWindowSize() = 0;
	virtual void run() = 0;
	virtual void drawRabbit (const coord_t &rabbit) = 0; 
	virtual void drawSnake (const Control::Snake &snake) = 0; 
	virtual void endHandler () = 0;
	virtual void drawBox() = 0;
	virtual ~View() = 0;

	virtual void addButton (const std::string &button, const std::function<void ()> &handler) = 0;
        virtual void eraseButton (const std::string &button) = 0;

	std::function<void ()> draw;
        std::function<int ()> move;
        //std::function<void ()> botsHandler;
        std::function<void ()> resizeHandler;
protected:
	std::chrono::milliseconds handTime = 200ms;
private:
	static inline const std::string_view textView = "text";
        static inline const std::string_view graphView = "graph";
};
}  // namespace graphicInterface

#endif // GAME_VIEW_H
