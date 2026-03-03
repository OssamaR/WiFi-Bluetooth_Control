#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <ncurses.h>
#include <string.h>
#include <cstdlib>

void print_centered(WINDOW *win, int row, int w, const char *text);
void state_machine(void);
void home_page(void);
void wifi_main(void);
void bluetooth_main(void);
void exit_state(void);

#endif