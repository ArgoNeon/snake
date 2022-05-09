CXX = g++
CXXFLAGS = -O0 -Wall -g -std=c++17
PROG = snake
SRCOBJ = tview.o gview.o model.o human.o view.o
OBJ = $(addprefix source/, $(SRCOBJ)) main.o
SRCDIR = . source
SRC = $(addsuffix /*.cpp, $(SRCDIR))

all: $(PROG)
clean:
	$(RM) $(OBJ) $(PROG)
depend: 
	$(CXX) -MM $(SRC) > .depend
$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(PROG)
-include .depend
