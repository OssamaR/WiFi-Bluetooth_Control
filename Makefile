all: main

main: main.cpp
	g++ main.cpp shared.cpp state_machine.cpp wifi_page.cpp bluetooth_page.cpp  -o a.out -lncurses
