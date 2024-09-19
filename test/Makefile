SRC=../src
OBJ=../obj
INC=../include
TEST=../test

CC=g++ -Wall -I$(INC)
# IDIRS= $$(pkg-config --cflags --libs Qt6Widgets) -fPIC
OBJS=main.o appcontroller.o rpncalc.o rpn.o
OBJSS=${OBJS:%=$(OBJ)/%}

FILES = $(wildcard *.cpp)
BIN = ${FILES:%.cpp=%}

tests: $(BIN)

%: %.cpp $(INC)/stack.h $(OBJSS)
	echo $(CC) $(IDIRS) -o $@ $^ "$(INC)/$@.h"
	$(CC) $(IDIRS) -o $@ $^ "$(INC)/$@.h"

# clean:
# 	rm -rf main *.o *.gch

.PHONY: clean

