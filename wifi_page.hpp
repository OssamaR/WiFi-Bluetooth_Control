#ifndef __WIFI_PAGE__
#define __WIFI_PAGE__

#include <ncurses.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <map>
#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>

#include "shared.hpp"


std::string cmd_output(const char* cmd);

void wifi_main(void);
void connect_to_a_network(void);
void display_wifi_status(void);

#endif