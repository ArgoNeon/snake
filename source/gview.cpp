#include "../include/gview.h"

namespace graphicInterface {

GView::GView() {

}

void GView::run() {
}

coord_t GView::getWindowSize() {
	coord_t nil = {0, 0};
	return nil;	
}

void GView::drawRabbit (const coord_t &rabbit) {
	
}

void GView::drawSnake (const Control::Snake &snake) {

}

void GView::endHandler(){

}

void GView::drawBox() {

}

void GView::addButton (const std::string &button, const std::function<void ()> &handler) {

}

void GView::eraseButton (const std::string &button) {

}
}  // namespace graphicInterface

