#include "../include/view.h"
#include "../include/tview.h"
#include "../include/gview.h"

namespace graphicInterface {

std::shared_ptr<View> View::get (const std::string &type) {
	if (!obj) {
		if (type == textView)
			obj = std::make_shared<TView> ();
		else if (type == graphView)
			obj = std::make_shared<GView> ();
		else
			throw std::logic_error ("Try \"text\" or \"graph\"");
		}

        return obj;
    }

View::~View() {};
}  // namespace graphicInterface
