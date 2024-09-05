main: main.o appcontroller.o rpncalc.o stack.o
	g++ $^ -o $@

main.o: main.cpp appcontroller.h
	g++ -c $<

appcontroller.o: appcontroller.cpp appcontroller.h rpncalc.h
	g++ -c $<

rpncalc.o: rpncalc.cpp rpncalc.h stack.h
	g++ -c $<

stack.o: stack.cpp stack.h
	g++ -c $<

clean:
	rm -rf *.o main

.PHONY: clean

