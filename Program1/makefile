# Makefile for program1 by Anna Phan

noArg: sloppySim.cpp
	g++ -Wall --std=c++17 sloppySim.cpp -o sloppySim -pthread
	time ./sloppySim

smallEx: sloppySim.cpp
	g++ -Wall --std=c++17 sloppySim.cpp -o sloppySim -pthread
	time ./sloppySim 4 5 11 100 false true

largeEx: sloppySim.cpp
	g++ -Wall --std=c++17 sloppySim.cpp -o sloppySim -pthread
	time ./sloppySim 80 5 11 100 false true 

cpuBoundEx: sloppySim.cpp
	g++ -Wall --std=c++17 sloppySim.cpp -o sloppySim -pthread
	time ./sloppySim 4 5 11 100 true true

clean:
	rm sloppySim