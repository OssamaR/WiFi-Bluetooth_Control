#include "shared.hpp"


void print_centered(WINDOW *win, int row, int w, const char *text) {
    int x = (w - (int)strlen(text)) / 2;
    if (x < 1) x = 1; // prevent overflow into border
    mvwprintw(win, row, x, text);
}