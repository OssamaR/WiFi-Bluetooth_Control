#ifndef __SHARED__
#define __SHARED__

#include <ncurses.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <map>
#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <sstream>

enum class state{
    HOME_PAGE,
    WIFI_MAIN,
    WIFI_CONNECT_TO_A_NETWORK,
    WIFI_DISPLAY_STATUS,
    WIFI_REMOVE_A_NETWORK,
    WIFI_MODIFY_NETWORK,
    WIFI_SEARCH_FOR_NETWORK,
    BLUETOOTH_MAIN,
    BLUETOOTH_DISPLAY_STATUS,
    BLUETOOTH_CONNECT_TO_DEVICE,
    EXIT
};

extern state machine;


void print_centered(WINDOW *win, int row, int w, const char *text);
std::string cmd_output(const char* cmd);


#endif