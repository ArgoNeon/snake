#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include<string>

class Coord{
public:
	int x;
	int y;
};

class view{
protected:
	Coord max_coord;
public:
	static view * get(const std::string& arg);
	static view * obj;
	Coord get_max_coord();
        void set_max_coord(int x, int y);
	//void paint(Coord);
	//void paint(string, int);
	//void paint(snake);
	virtual void MainLoop() = 0;
	virtual void draw() = 0;
	virtual void run() = 0;
	virtual ~view() {};
private:

};

#endif // GAME_VIEW_H
