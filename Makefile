all: main

main: main.cpp
	g++ main.cpp state_machine.cpp -o a.out -lncurses
