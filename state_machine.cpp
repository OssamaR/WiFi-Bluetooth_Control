#include "state_machine.hpp"



state machine = state::HOME_PAGE ;

  enum class selection {
    wifi,
    bluetooth,
    exit
};



/*
Main state machine code
*/
void state_machine(void)
{
    switch (machine)
    {
    case state::HOME_PAGE:
        home_page();
        break;

    case state::WIFI_MAIN:
        wifi_main();
        break;

    case state::WIFI_CONNECT_TO_A_NETWORK:
        connect_to_a_network();
        break;
    case state::WIFI_DISPLAY_STATUS:
        display_wifi_status();
        break;

    case state::WIFI_REMOVE_A_NETWORK:
        remove_network();
        break;

    case state::WIFI_MODIFY_NETWORK:
        modify_network();
        break;

    case state::WIFI_SEARCH_FOR_NETWORK:
        search_for_network();
        break;

    case state::BLUETOOTH_MAIN:
        bluetooth_main();
        break;

    case state::BLUETOOTH_DISPLAY_STATUS:
        display_bluetooth_status();
        break;

    case state::BLUETOOTH_CONNECT_TO_DEVICE:
        connect_to_bluetooth();
        break;
    
    
    case state::EXIT:
        exit_state();
        break;

    default:
        break;
    }
}


void home_page(void)
{
    static selection select = selection::wifi;
    // initialize the screen, sets up memory and clears screen
    
    int h, w, line_start, space_start;
    h=7;
    w=80;
    line_start =0;
    space_start =0;
 // creates the window
    static WINDOW * controlprogram_win = newwin(h, w, line_start, space_start);
    wbkgd(controlprogram_win, ' ' | COLOR_PAIR(0));
    static WINDOW * wifi_win = newwin(h, w, line_start+ h-1, space_start);
    wbkgd(wifi_win, ' ' | COLOR_PAIR(0));
    static WINDOW * bluetooth_win = newwin(h, w, line_start+ 2*h-2, space_start);
    wbkgd(bluetooth_win, ' ' | COLOR_PAIR(0));
    static WINDOW * exit_win = newwin(h, w, line_start+ 3*h-3, space_start);
    wbkgd(exit_win, ' ' | COLOR_PAIR(0));
    refresh(); // refreshes the entire screen

    // puts a border around the window
    box(controlprogram_win, 0, 0);
    // wborder(controlprogram_win,0,0,0,' ',0,0,' ',' ');
    // mvwprintw(controlprogram_win, 1, 1, "Main Menu");

    // box(wifi_win, 0, 0);
    wborder(wifi_win,0,0,0,0,'+','+','+','+'); 
    // mvwprintw(wifi_win, 1, 1, "Wi-Fi");

    wborder(bluetooth_win,0,0,0,0,'+','+','+','+'); 


    box(exit_win, 0, 0);
    // mvwprintw(bluetooth_win, 1, 1, "Bluetooth");

    wattron(controlprogram_win, A_BOLD);
    print_centered(controlprogram_win, 3, w, "Control Program");
    wattroff(wifi_win, A_BOLD);


    // wattron(wifi_win, A_REVERSE// puts a border around the window
    box(controlprogram_win, 0, 0);
    // wborder(controlprogram_win,0,0,0,' ',0,0,' ',' ');
    // mvwprintw(controlprogram_win, 1, 1, "Main Menu");

    // box(wifi_win, 0, 0);
    wborder(wifi_win,0,0,0,0,'+','+','+','+'); 
    // mvwprintw(wifi_win, 1, 1, "Wi-Fi");

    wborder(bluetooth_win,0,0,0,0,'+','+','+','+'); 


    box(exit_win, 0, 0);
    // mvwprintw(bluetooth_win, 1, 1, "Bluetooth");

    wattron(controlprogram_win, A_BOLD);
    print_centered(controlprogram_win, 3, w, "Control Program");
    wattroff(wifi_win, A_BOLD);


    // wattron(wifi_win, A_REVERSE);
    print_centered(wifi_win, 3, w, "Wi-Fi");
    // wattroff(wifi_win, A_REVERSE);

    print_centered(bluetooth_win, 3, w, "Bluetooth");
    print_centered(exit_win, 3, w, "Exit");

    wrefresh(controlprogram_win); // refreshes a specific window
    wrefresh(exit_win);
    wrefresh(bluetooth_win);
    wrefresh(wifi_win);
    
    

    switch(select){
        case selection::wifi:
            wattron(wifi_win, A_REVERSE);
            print_centered(wifi_win, 3, w, "Wi-Fi");
            wattroff(wifi_win, A_REVERSE);

            select = selection::wifi;
        break;

        case selection::bluetooth:

            wattron(bluetooth_win, A_REVERSE);
            print_centered(bluetooth_win, 3, w, "Bluetooth");
            wattroff(bluetooth_win, A_REVERSE);

            select = selection::bluetooth;
        break;

        case selection::exit:

            wattron(exit_win, A_REVERSE);
            print_centered(exit_win, 3, w, "Exit");
            wattroff(exit_win, A_REVERSE);

            select = selection::exit;
        break;
    }

        wrefresh(exit_win);
        wrefresh(bluetooth_win);
        wrefresh(wifi_win);


    int key_pressed;

   while(1)
    {
        key_pressed= getch();
        if(key_pressed== KEY_UP){ 
            switch(select){
                case selection::wifi:
                    // do nothing
                break;

                case selection::bluetooth:

                    wattron(wifi_win, A_REVERSE);
                    print_centered(wifi_win, 3, w, "Wi-Fi");
                    wattroff(wifi_win, A_REVERSE);

                    wattron(bluetooth_win, A_NORMAL);
                    print_centered(bluetooth_win, 3, w, "Bluetooth");
                    wattroff(bluetooth_win, A_NORMAL);

                    select = selection::wifi;
                break;

                case selection::exit:

                    wattron(bluetooth_win, A_REVERSE);
                    print_centered(bluetooth_win, 3, w, "Bluetooth");
                    wattroff(bluetooth_win, A_REVERSE);

                    wattron(exit_win, A_NORMAL);
                    print_centered(exit_win, 3, w, "Exit");
                    wattroff(exit_win, A_NORMAL);

                    select = selection::bluetooth;
                break;
            }
        }
        else if(key_pressed== KEY_DOWN){
            switch(select){
                case selection::wifi:
                    wattron(wifi_win, A_NORMAL);
                    print_centered(wifi_win, 3, w, "Wi-Fi");
                    wattroff(wifi_win, A_NORMAL);

                    wattron(bluetooth_win, A_REVERSE);
                    print_centered(bluetooth_win, 3, w, "Bluetooth");
                    wattroff(bluetooth_win, A_REVERSE);

                    select = selection::bluetooth;
                break;

                case selection::bluetooth:
                    wattron(bluetooth_win, A_NORMAL);
                    print_centered(bluetooth_win, 3, w, "Bluetooth");
                    wattroff(bluetooth_win, A_NORMAL);

                    wattron(exit_win, A_REVERSE);
                    print_centered(exit_win, 3, w, "Exit");
                    wattroff(exit_win, A_REVERSE);

                    select = selection::exit;
                    
                break;

                case selection::exit:
                    // Do nothing
                break;
            }
        }
        else if (key_pressed == '\n' || key_pressed == KEY_ENTER || key_pressed == '\r')
        {
            // go to page depending on the selection enum
            switch (select)
            {
            case selection::wifi:
                machine=state::WIFI_MAIN;
                break;
            
            case selection::bluetooth:
                machine=state::BLUETOOTH_MAIN;
                break;

            case selection::exit:
                machine=state::EXIT;
                break;
            }
            break;
        }

        wrefresh(exit_win);
        wrefresh(bluetooth_win);
        wrefresh(wifi_win);

        

    }

    werase(controlprogram_win);
    werase(wifi_win);
    werase(bluetooth_win);
    werase(exit_win);
}


void exit_state(void)
{
    endwin();
    exit(0);
}