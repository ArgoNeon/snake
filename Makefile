CXX = g++
CXXFLAGS = -O0 -Wall
PROG = snake
OBJ = tview.o gview.o model.o human.o main.o view.o

all: $(PROG)
clean:
	$(RM) $(OBJ) $(PROG)
depend: 
	$(CXX) -MM $(CXXFLAGS) *.cpp > .depend
$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(PROG)
-include .depend
