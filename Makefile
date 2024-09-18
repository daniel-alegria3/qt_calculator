SRC=src
OBJ=obj
INC=include
TEST=test

CC=g++ -Wall -I$(INC)
# IDIRS= $$(pkg-config --cflags --libs Qt6Widgets) -fPIC
OBJS=main.o appcontroller.o rpncalc.o rpn.o undoredo.o
OBJSS=${OBJS:%=$(OBJ)/%}

main: $(OBJSS)
	$(CC) $(IDIRS) -o $@ $^

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/appcontroller.h
	$(CC) $(IDIRS) -c $< -o $@

$(OBJ)/appcontroller.o: $(SRC)/appcontroller.cpp $(INC)/appcontroller.h $(INC)/rpncalc.h
	$(CC) -c $< -o $@

$(OBJ)/rpncalc.o: $(SRC)/rpncalc.cpp $(INC)/rpncalc.h $(INC)/stack.h
	$(CC) -c $< -o $@

$(OBJ)/rpn.o: $(SRC)/rpn.cpp $(INC)/rpn.h $(INC)/stack.h
	$(CC) -c $< -o $@

$(OBJ)/undoredo.o: $(SRC)/undoredo.cpp $(INC)/stack.h
	$(CC) -c $< -o $@

# stack.o: stack.cpp stack.h
# 	$(CC) -c stack.h -o $@

clean:
	rm -rf main *.o *.gch obj/*

.PHONY: clean

