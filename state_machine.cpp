#include "state_machine.hpp"

enum class state{
    HOME_PAGE,
    WIFI_MAIN,
    BLUETOOTH_MAIN,
    EXIT
};

state machine = state::HOME_PAGE ;

  enum class selection {
    wifi,
    bluetooth,
    exit
};

void print_centered(WINDOW *win, int row, int w, const char *text) {
    int x = (w - (int)strlen(text)) / 2;
    if (x < 1) x = 1; // prevent overflow into border
    mvwprintw(win, row, x, text);
}

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

    case state::BLUETOOTH_MAIN:
        bluetooth_main();
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
    initscr();
    cbreak();
    // raw();
    noecho();
    keypad(stdscr, TRUE);
    // printw("Hello World!");

    int h, w, line_start, space_start;
    h=7;
    w=80;
    line_start =0;
    space_start =0;
 // creates the window
    static WINDOW * controlprogram_win = newwin(h, w, line_start, space_start);
    static WINDOW * wifi_win = newwin(h, w, line_start+ h-1, space_start);
    static WINDOW * bluetooth_win = newwin(h, w, line_start+ 2*h-2, space_start);
    static WINDOW * exit_win = newwin(h, w, line_start+ 3*h-3, space_start);
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
    
    curs_set(0);

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
        else if( key_pressed== '\n')
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

void wifi_main(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
 
    static WINDOW * wifi_home = newwin(5,   w, line_start, space_start);
    static WINDOW * wifi_menu = newwin(h-4, w, 4, space_start);
    refresh();

    box(wifi_home, 0, 0);
    wborder(wifi_menu,0,0,0,0,'+','+',0,0); 

    wrefresh(wifi_home);
    wrefresh(wifi_menu);

    getch();
}

void bluetooth_main(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
 
    static WINDOW * bluetooth_home = newwin(5,   w, line_start, space_start);
    static WINDOW * bluetooth_menu = newwin(h-4, w, 4, space_start);
    refresh();

    box(bluetooth_home, 0, 0);
    wborder(bluetooth_menu,0,0,0,0,'+','+',0,0); 

    wrefresh(bluetooth_home);
    wrefresh(bluetooth_menu);

    getch();
}


void exit_state(void)
{
    endwin();
    exit(0);
}