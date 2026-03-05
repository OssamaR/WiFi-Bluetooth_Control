#ifndef __STATE_MACHINE__
#define __STATE_MACHINE__

#include <ncurses.h>
#include <string.h>
#include <string>
#include <cstdlib>

#include <iostream>
#include <cstdio>
#include <memory>

#include "wifi_page.hpp"
#include "shared.hpp"



// std::string cmd_output(const char* cmd);

void state_machine(void);
void home_page(void);
// void wifi_main(void);
void bluetooth_main(void);
void exit_state(void);

#endif