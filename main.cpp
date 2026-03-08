#include "state_machine.hpp"


int main(int argc, char ** argv)
{
    initscr();
    cbreak();
    // raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);   // pair 1 = green text, black background
    init_pair(2, COLOR_RED, COLOR_BLACK);

    bkgd(' ' | COLOR_PAIR(0));   // Fill the root screen with black background
    refresh();
    while(1)
    {
        state_machine();
    }
    return 0;
}