CC=g++ -Wall
IDIRS= $$(pkg-config --cflags --libs Qt6Widgets) -fPIC

main: main.o appcontroller.o rpncalc.o stack.h
	$(CC) $(IDIRS) -o $@ $^

main.o: main.cpp appcontroller.h
	$(CC) $(IDIRS) -c $< -o $@

appcontroller.o: appcontroller.cpp appcontroller.h rpncalc.h
	$(CC) -c $< -o $@

rpncalc.o: rpncalc.cpp rpncalc.h stack.h
	$(CC) -c $< -o $@

# stack.o: stack.cpp stack.h
# 	$(CC) -c stack.h -o $@

clean:
	rm -rf *.o main

.PHONY: clean

