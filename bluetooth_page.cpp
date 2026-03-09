#include "bluetooth_page.hpp"



void bluetooth_main(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
    int key;
    static WINDOW * bluetooth_home = newwin(5,   w, line_start, space_start);
    wbkgd(bluetooth_home, COLOR_PAIR(0));
    static WINDOW * bluetooth_status = newwin(3, w, line_start+4, space_start);
    wbkgd(bluetooth_status, COLOR_PAIR(0));
    static WINDOW * bluetooth_menu = newwin(h-6, w, 6, space_start);
    wbkgd(bluetooth_menu, COLOR_PAIR(0));

    std::vector<std::string> menu_items = {
        "[ Display Bluetooth Status ]",
        "[ Turn Bluetooth ON ]",
        "[ Turn Bluetooth OFF ]",
        "[ Connect to Bluetooth Device ]",
        "[ Back to main menu ]"
    };

    std::vector<std::string> menu_OFF_items = {
        "[ Turn Bluetooth ON ]",
        "[ Back to main menu ]"
    };

    refresh();
    box(bluetooth_home, 0, 0);
    wborder(bluetooth_status,0,0,0,0,'+','+','+','+'); 
    wborder(bluetooth_menu,0,0,0,0,'+','+',0,0); 

    
    int index_ON=0;
    int index_OFF=0;
    refresh();
    
    wattron(bluetooth_home,A_BOLD);
    print_centered(bluetooth_home, 2, w, "Bluetooth Control");
    wattroff(bluetooth_home,A_BOLD);

    mvwprintw(bluetooth_status, 1, 2, "Status:");
    if(cmd_output("bluetoothctl show | grep \"Powered\"") == "	Powered: yes")
    {
        wattron(bluetooth_status,COLOR_PAIR(1));
        mvwprintw(bluetooth_status, 1, 10, "ON");
        wattroff(bluetooth_status,COLOR_PAIR(1));


        std::string result = cmd_output("bluetoothctl info | grep \"Name\" ");
        if(!result.empty())
        {
            // parse "Name: DeviceName" → get everything after ": "
            std::string device_name = result.substr(result.find(": ") + 2);
            mvwprintw(bluetooth_status, 1, 13, "|| Connected to: %s", device_name.c_str());
        }
        else
        {
            mvwprintw(bluetooth_status, 1, 13, "|| No Device Connected");
        }

        wattron(bluetooth_menu, A_REVERSE);
        mvwprintw(bluetooth_menu, 1, 1, "[ Display Bluetooth Status ]");
        wattroff(bluetooth_menu, A_REVERSE);
        mvwprintw(bluetooth_menu, 2, 1, "[ Turn Bluetooth ON ]");
        mvwprintw(bluetooth_menu, 3, 1, "[ Turn Bluetooth OFF ]");
        mvwprintw(bluetooth_menu, 4, 1, "[ Connect to Bluetooth Device ]");
        mvwprintw(bluetooth_menu, 5, 1, "[ Back to main menu ]");

    }
    else
    {
        wattron(bluetooth_status,COLOR_PAIR(2));
        mvwprintw(bluetooth_status, 1, 10, "OFF");
        wattroff(bluetooth_status,COLOR_PAIR(2));

        wattron(bluetooth_menu, A_REVERSE);
        mvwprintw(bluetooth_menu, 1, 1, "[ Turn Bluetooth ON ]");
        wattroff(bluetooth_menu, A_REVERSE);
        mvwprintw(bluetooth_menu, 2, 1, "[ Back to main menu ]");
    }
  

    refresh();

    wrefresh(bluetooth_home);
    
    wrefresh(bluetooth_menu);
    wrefresh(bluetooth_status);


    while(1)
    {
        
        // key=getch();


        if(cmd_output("bluetoothctl show | grep \"Powered\"") == "	Powered: yes")
        {
            wattron(bluetooth_status,COLOR_PAIR(1));
            mvwprintw(bluetooth_status, 1, 10, "ON ");
            wattroff(bluetooth_status,COLOR_PAIR(1));


            std::string result = cmd_output("bluetoothctl info | grep \"Name\" ");
            if(!result.empty())
            {
                // parse "Name: DeviceName" → get everything after ": "
                std::string device_name = result.substr(result.find(": ") + 2);
                mvwprintw(bluetooth_status, 1, 13, "|| Connected to: %s", device_name.c_str());
            }
            else
            {
                mvwprintw(bluetooth_status, 1, 13, "|| No Device Connected");
            }


            mvwprintw(bluetooth_menu, 1, 1, "[ Display Bluetooth Status ]");
            mvwprintw(bluetooth_menu, 2, 1, "[ Turn Bluetooth ON ]");
            mvwprintw(bluetooth_menu, 3, 1, "[ Turn Bluetooth OFF ]");
            mvwprintw(bluetooth_menu, 4, 1, "[ Connect to Bluetooth Device ]");
            mvwprintw(bluetooth_menu, 5, 1, "[ Back to main menu ]");



            wattron(bluetooth_menu,A_REVERSE);
            mvwprintw(bluetooth_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
            wattroff(bluetooth_menu,A_REVERSE);

            wrefresh(bluetooth_menu);
            wrefresh(bluetooth_status);
                



            key=getch();
            if(key == KEY_UP )
            {
                if(index_ON == 0) index_ON=4;
                else index_ON--;
            }
            else if(key == KEY_DOWN)
            {
                if(index_ON == 4) index_ON=0;
                else index_ON++;
                
            }
            else if(key == '\n')
            {
                switch(index_ON)
                {
                    case 0:
                        machine = state::BLUETOOTH_DISPLAY_STATUS;
                    break;

                    case 1:
                        cmd_output("bluetoothctl power on");
                    break;

                    case 2:
                        cmd_output("bluetoothctl power off");
                    break;

                    case 3:
                        machine = state::BLUETOOTH_CONNECT_TO_DEVICE;
                    break;

                    case 4:
                        machine = state::HOME_PAGE;
                    break;
                
                }
                if( index_ON !=1 && index_ON !=2) break;            
            }
        }
        else
        {
            werase(bluetooth_status);
            wborder(bluetooth_status,0,0,0,0,'+','+','+','+');
            werase(bluetooth_menu);
            wborder(bluetooth_menu, 0,0,0,0,'+','+',0,0);
            mvwprintw(bluetooth_status, 1, 2, "Status:");
            wattron(bluetooth_status,COLOR_PAIR(2));
            mvwprintw(bluetooth_status, 1, 10, "OFF");
            wattroff(bluetooth_status,COLOR_PAIR(2));
        

            mvwprintw(bluetooth_menu, 1, 1, "[ Turn Bluetooth ON ]");
            mvwprintw(bluetooth_menu, 2, 1, "[ Back to main menu ]");
           
            wattron(bluetooth_menu, A_REVERSE);
            mvwprintw(bluetooth_menu, index_OFF+1, 1, "%s",menu_OFF_items[index_OFF].c_str());
            wattroff(bluetooth_menu, A_REVERSE);
         
      
                
            wrefresh(bluetooth_home);
            wrefresh(bluetooth_menu);
            wrefresh(bluetooth_status);
            refresh();
            
            key=getch();

            if(key == KEY_UP)
            {
                if(index_OFF==1) index_OFF--;
            }
            else if(key == KEY_DOWN)
            {
                if(index_OFF==0) index_OFF++;
            }
            else if(key == '\n')
            {
                if(index_OFF == 0)
                {
                    cmd_output("bluetoothctl power on");
                }
                else
                {
                    machine = state::HOME_PAGE;
                    break;
                }
            }
            
        }

        wrefresh(bluetooth_home);
        wrefresh(bluetooth_menu);
        wrefresh(bluetooth_status);
    }
    werase(bluetooth_home);
    werase(bluetooth_menu);
    werase(bluetooth_status);
    
}

void display_bluetooth_status(void)
{
    int h=7*4-3, w=80;
    static WINDOW* bt_menu = newwin(h-6, w, 6, 0);

    wbkgd(bt_menu, COLOR_PAIR(0));
    wborder(bt_menu,0,0,0,0,'+','+',0,0);
    wrefresh(bt_menu);

    std::string powered  = cmd_output("bluetoothctl show | grep 'Powered'");
    std::string name     = cmd_output("bluetoothctl info | grep 'Name'");
    std::string device   = cmd_output("bluetoothctl info | grep 'Connected'");
    std::string mac      = cmd_output("bluetoothctl show | grep 'Controller'");

    mvwprintw(bt_menu, 1, 2, "State     : %s", powered.empty()  ? "N/A" : powered.substr(powered.find(':')+2).c_str());
    mvwprintw(bt_menu, 2, 2, "Controller: %s", mac.empty()      ? "N/A" : mac.substr(mac.find(' ')+1).c_str());
    mvwprintw(bt_menu, 3, 2, "Connected : %s", device.empty()   ? "no"  : device.substr(device.find(':')+2).c_str());
    mvwprintw(bt_menu, 4, 2, "Device    : %s", name.empty()     ? "N/A" : name.substr(name.find(':')+2).c_str());

    mvwprintw(bt_menu, 6, 2, "Press any key to go back...");
    wrefresh(bt_menu);
    getch();

    machine = state::BLUETOOTH_MAIN;
    wclear(bt_menu);
    wrefresh(bt_menu);
}


void connect_to_bluetooth(void)
{
    int h=7*4-3, w=80;
    static WINDOW* bt_menu = newwin(h-6, w, 6, 0);

    wbkgd(bt_menu, COLOR_PAIR(0));
    wborder(bt_menu,0,0,0,0,'+','+',0,0);
    wrefresh(bt_menu);

    mvwprintw(bt_menu, 1, 1, "Device MAC Address: ");
    wrefresh(bt_menu);

    echo();
    curs_set(1);

    char mac_buf[64] = {0};
    wgetstr(bt_menu, mac_buf);
    std::string mac(mac_buf);

    curs_set(0);
    noecho();

    // Pair and connect
    std::string cmd = "bluetoothctl pair " + mac + " > /dev/null 2>&1";
    int ret = system(cmd.c_str());
    refresh();

    if(ret == 0)
    {
        // Trust and connect after pairing
        std::string cmd2 = "bluetoothctl trust " + mac + " > /dev/null 2>&1";
        system(cmd2.c_str());
        refresh();

        std::string cmd3 = "bluetoothctl connect " + mac + " > /dev/null 2>&1";
        ret = system(cmd3.c_str());
        refresh();
    }

    if(ret == 0)
    {
        wattron(bt_menu, COLOR_PAIR(1));
        mvwprintw(bt_menu, 3, 1, "Connected successfully!");
        wattroff(bt_menu, COLOR_PAIR(1));
    }
    else
    {
        wattron(bt_menu, COLOR_PAIR(2));
        mvwprintw(bt_menu, 3, 1, "Failed to connect.");
        wattroff(bt_menu, COLOR_PAIR(2));
    }

    wrefresh(bt_menu);
    getch();

    machine = state::BLUETOOTH_MAIN;
    werase(bt_menu);
    wrefresh(bt_menu);
}