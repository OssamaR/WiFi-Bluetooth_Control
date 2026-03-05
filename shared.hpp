#ifndef __SHARED__
#define __SHARED__

#include <ncurses.h>
#include <string.h>
#include <string>

enum class state{
    HOME_PAGE,
    WIFI_MAIN,
    WIFI_CONNECT_TO_A_NETWORK,
    WIFI_DISPLAY_STATUS,
    WIFI_REMOVE_A_NETWORK,
    BLUETOOTH_MAIN,
    EXIT
};

extern state machine;


void print_centered(WINDOW *win, int row, int w, const char *text);
#endif