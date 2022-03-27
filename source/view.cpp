#include "../include/view.h"
#include "../include/tview.h"
#include "../include/gview.h"

view * view::obj;

view * view::get(const std::string& arg) {
	if (!obj) {
	if (arg == "text") {
		tview * tv = new tview();
		obj = tv;
	}
	if (arg == "graph") {
		gview * gv = new gview();
		obj = gv; 
	}
	}
	return obj;
}

Coord view::get_max_coord(){
    return view::max_coord;
}

void view::set_max_coord(int x, int y){
    view::max_coord.x = x;
    view::max_coord.y = y;
}
