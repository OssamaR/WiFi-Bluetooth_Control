#include "wifi_page.hpp"

// enum class state{
//     HOME_PAGE,
//     WIFI_MAIN,
//     BLUETOOTH_MAIN,
//     EXIT
// };

// state machine = state::HOME_PAGE ;


std::string cmd_output(const char* cmd)
{
    // const char* cmd = "nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes' ";
    
    std::string result;
    char buffer[128];

    // Open pipe to read command output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        // std::cerr << "popen() failed!" << std::endl;
        return "popen() failed!";
    }

    // Read output into result
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // Remove trailing newline
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}    
    

// void wifi_menu_selection(void)
// {

//     while(1)
//     {
//         key_pressed= getch();
//         if(key_pressed== KEY_UP){ 
//             switch(select){
//                 case selection::wifi:
//                     // do nothing
//                 break;

//                 case selection::bluetooth:

//                     wattron(wifi_win, A_REVERSE);
//                     print_centered(wifi_win, 3, w, "Wi-Fi");
//                     wattroff(wifi_win, A_REVERSE);

//                     wattron(bluetooth_win, A_NORMAL);
//                     print_centered(bluetooth_win, 3, w, "Bluetooth");
//                     wattroff(bluetooth_win, A_NORMAL);

//                     select = selection::wifi;
//                 break;

//                 case selection::exit:

//                     wattron(bluetooth_win, A_REVERSE);
//                     print_centered(bluetooth_win, 3, w, "Bluetooth");
//                     wattroff(bluetooth_win, A_REVERSE);

//                     wattron(exit_win, A_NORMAL);
//                     print_centered(exit_win, 3, w, "Exit");
//                     wattroff(exit_win, A_NORMAL);

//                     select = selection::bluetooth;
//                 break;
//             }
//         }
//         else if(key_pressed== KEY_DOWN){
//             switch(select){
//                 case selection::wifi:
//                     wattron(wifi_win, A_NORMAL);
//                     print_centered(wifi_win, 3, w, "Wi-Fi");
//                     wattroff(wifi_win, A_NORMAL);

//                     wattron(bluetooth_win, A_REVERSE);
//                     print_centered(bluetooth_win, 3, w, "Bluetooth");
//                     wattroff(bluetooth_win, A_REVERSE);

//                     select = selection::bluetooth;
//                 break;

//                 case selection::bluetooth:
//                     wattron(bluetooth_win, A_NORMAL);
//                     print_centered(bluetooth_win, 3, w, "Bluetooth");
//                     wattroff(bluetooth_win, A_NORMAL);

//                     wattron(exit_win, A_REVERSE);
//                     print_centered(exit_win, 3, w, "Exit");
//                     wattroff(exit_win, A_REVERSE);

//                     select = selection::exit;
                    
//                 break;

//                 case selection::exit:
//                     // Do nothing
//                 break;
//             }
//         }
//         else if( key_pressed== '\n')
//         {
//             // go to page depending on the selection enum
//             switch (select)
//             {
//             case selection::wifi:
//                 machine=state::WIFI_MAIN;
//                 break;
            
//             case selection::bluetooth:
//                 machine=state::BLUETOOTH_MAIN;
//                 break;

//             case selection::exit:
//                 machine=state::EXIT;
//                 break;
//             }
//             break;
//         }

// }



void wifi_main(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
    int key;
    static WINDOW * wifi_home = newwin(5,   w, line_start, space_start);
    wbkgd(wifi_home, COLOR_PAIR(0));
    static WINDOW * wifi_status = newwin(3, w, line_start+4, space_start);
    wbkgd(wifi_status, COLOR_PAIR(0));
    static WINDOW * wifi_menu = newwin(h-6, w, 6, space_start);
    wbkgd(wifi_menu, COLOR_PAIR(0));

    std::vector<std::string> menu_items = {
        "[ Display WiFi Status ]",
        "[ Turn WiFi ON ]",
        "[ Turn WiFi OFF ]",
        "[ Connect to WiFi Network ]",
        "[ Remove a Saved Network ]",
        "[ Modify a Saved Network ]",
        "[ Search for a Network ]",
        "[ Back to main menu ]"
    };

    std::vector<std::string> menu_OFF_items = {
        "[ Turn WiFi ON ]",
        "[ Back to main menu ]"
    };

    refresh();
    box(wifi_home, 0, 0);
    wborder(wifi_status,0,0,0,0,'+','+','+','+'); 
    wborder(wifi_menu,0,0,0,0,'+','+',0,0); 

    
    int index_ON=0;
    int index_OFF=0;
    refresh();
    
    wattron(wifi_home,A_BOLD);
    print_centered(wifi_home, 2, w, "WiFi Control");
    wattroff(wifi_home,A_BOLD);

    mvwprintw(wifi_status, 1, 2, "Status:");
    if(cmd_output("nmcli radio wifi") == "enabled")
    {
        wattron(wifi_status,COLOR_PAIR(1));
        mvwprintw(wifi_status, 1, 10, "ON");
        wattroff(wifi_status,COLOR_PAIR(1));

        std::string result = cmd_output("nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes' ");
        if(result[0]=='y')
        {
            mvwprintw(wifi_status, 1, 13, "|| Connected to:");
            result = result.substr( result.find(':')+1);
            mvwprintw(wifi_status, 1, 30, "%s", result.c_str());
        }
        else
        {
            mvwprintw(wifi_status, 1, 14, "| No Network Connection");
        }

        wattron(wifi_menu, A_REVERSE);
        mvwprintw(wifi_menu, 1, 1, "[ Display WiFi Status ]");
        wattroff(wifi_menu, A_REVERSE);
        mvwprintw(wifi_menu, 2, 1, "[ Turn WiFi ON ]");
        mvwprintw(wifi_menu, 3, 1, "[ Turn WiFi OFF ]");
        mvwprintw(wifi_menu, 4, 1, "[ Connect to WiFi Network ]");
        mvwprintw(wifi_menu, 5, 1, "[ Remove a Saved Network ]");
        mvwprintw(wifi_menu, 6, 1, "[ Modify a Saved Network ]");
        mvwprintw(wifi_menu, 7, 1, "[ Search for a Network ]");
        mvwprintw(wifi_menu, 8, 1, "[ Back to main menu ]");

        // wifi_menu_selection();

       
    
    }
    else
    {
        wattron(wifi_status,COLOR_PAIR(2));
        mvwprintw(wifi_status, 1, 10, "OFF");
        wattroff(wifi_status,COLOR_PAIR(2));

        wattron(wifi_menu, A_REVERSE);
        mvwprintw(wifi_menu, 1, 1, "[ Turn WiFi ON ]");
        wattroff(wifi_menu, A_REVERSE);
        mvwprintw(wifi_menu, 2, 1, "[ Back to main menu ]");
    }
  

    refresh();

    wrefresh(wifi_home);
    
    wrefresh(wifi_menu);
    wrefresh(wifi_status);


    while(1)
    {
        
        // key=getch();


        if(cmd_output("nmcli radio wifi") == "enabled")
        {
            werase(wifi_status);
            werase(wifi_menu);
            wborder(wifi_status,0,0,0,0,'+','+','+','+'); 
            wborder(wifi_menu,0,0,0,0,'+','+',0,0); 
            mvwprintw(wifi_status, 1, 2, "Status:");

            mvwprintw(wifi_menu, 1, 1, "[ Display WiFi Status ]");
            mvwprintw(wifi_menu, 2, 1, "[ Turn WiFi ON ]");
            mvwprintw(wifi_menu, 3, 1, "[ Turn WiFi OFF ]");
            mvwprintw(wifi_menu, 4, 1, "[ Connect to WiFi Network ]");
            mvwprintw(wifi_menu, 5, 1, "[ Remove a Saved Network ]");
            mvwprintw(wifi_menu, 6, 1, "[ Modify a Saved Network ]");
            mvwprintw(wifi_menu, 7, 1, "[ Search for a Network ]");
            mvwprintw(wifi_menu, 8, 1, "[ Back to main menu ]");

            wattron(wifi_status,COLOR_PAIR(1));
            mvwprintw(wifi_status, 1, 10, "ON");
            wattroff(wifi_status,COLOR_PAIR(1));

            std::string result = cmd_output("nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes' ");
            if(result[0]=='y')
            {
                mvwprintw(wifi_status, 1, 13, "|| Connected to:");
                result = result.substr( result.find(':')+1);
                mvwprintw(wifi_status, 1, 30, "%s", result.c_str());
            }
            else
            {
                mvwprintw(wifi_status, 1, 14, "| No Network Connection");
            }


            wattron(wifi_menu,A_REVERSE);
            mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
            wattroff(wifi_menu,A_REVERSE);

            wrefresh(wifi_menu);
            wrefresh(wifi_status);
                



            key=getch();
            if(key == KEY_UP )
            {
                if(index_ON == 0) index_ON=7;
                else index_ON--;
                // if(index_ON==0)
                // {
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     index_ON=7;
                //     wattron(wifi_menu,A_REVERSE);
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     wattroff(wifi_menu,A_REVERSE);
                // }
                // else
                // {
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     index_ON--;
                //     wattron(wifi_menu,A_REVERSE);
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     wattroff(wifi_menu,A_REVERSE);
                // }
            }
            else if(key == KEY_DOWN)
            {
                if(index_ON == 7) index_ON=0;
                else index_ON++;
                // if(index_ON==7)
                // {
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     index_ON=0;
                //     wattron(wifi_menu,A_REVERSE);
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     wattroff(wifi_menu,A_REVERSE);
                // }
                // else
                // {
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     index_ON++;
                //     wattron(wifi_menu,A_REVERSE);
                //     mvwprintw(wifi_menu, index_ON+1, 1, "%s" ,menu_items[index_ON].c_str());
                //     wattroff(wifi_menu,A_REVERSE);
                // }
            }
            else if(key == '\n')
            {
                switch(index_ON)
                {
                    case 0:
                        machine = state::WIFI_DISPLAY_STATUS;
                    break;

                    case 1:
                        cmd_output("nmcli radio wifi on");
                    break;

                    case 2:
                        cmd_output("nmcli radio wifi off");
                    break;

                    case 3:
                        machine = state::WIFI_CONNECT_TO_A_NETWORK;
                    break;

                    case 4:
                        machine = state::WIFI_REMOVE_A_NETWORK;
                    break;

                    case 5:
                        machine = state::WIFI_MODIFY_NETWORK;
                    break;

                    case 6:
                        machine = state::WIFI_SEARCH_FOR_NETWORK;
                    break;

                    case 7:
                        machine = state::HOME_PAGE;
                    break;
                
                }
                if( index_ON !=1 && index_ON !=2) break;            
            }
        }
        else
        {
            werase(wifi_status);
            wborder(wifi_status,0,0,0,0,'+','+','+','+');
            werase(wifi_menu);
            wborder(wifi_menu, 0,0,0,0,'+','+',0,0);
            mvwprintw(wifi_status, 1, 2, "Status:");
            wattron(wifi_status,COLOR_PAIR(2));
            mvwprintw(wifi_status, 1, 10, "OFF");
            wattroff(wifi_status,COLOR_PAIR(2));
        

            mvwprintw(wifi_menu, 1, 1, "[ Turn WiFi ON ]");
            mvwprintw(wifi_menu, 2, 1, "[ Back to main menu ]");
           
            wattron(wifi_menu, A_REVERSE);
            mvwprintw(wifi_menu, index_OFF+1, 1, "%s",menu_OFF_items[index_OFF].c_str());
            wattroff(wifi_menu, A_REVERSE);
         
      
                
            wrefresh(wifi_home);
            wrefresh(wifi_menu);
            wrefresh(wifi_status);
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
                    cmd_output("nmcli radio wifi on");
                }
                else
                {
                    machine = state::HOME_PAGE;
                    break;
                }
            }
            
        }

        wrefresh(wifi_home);
        wrefresh(wifi_menu);
        wrefresh(wifi_status);
    }
    werase(wifi_home);
    werase(wifi_menu);
    werase(wifi_status);
    
}


void connect_to_a_network(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
    int key;
    static WINDOW * wifi_menu = newwin(h-6, w, 6, space_start);
    wbkgd(wifi_menu, COLOR_PAIR(0));

    wborder(wifi_menu,0,0,0,0,'+','+',0,0); 

   
    wrefresh(wifi_menu);
    

    

    mvwprintw(wifi_menu,1,1,"Network Name: ");
    wrefresh(wifi_menu);
    refresh();
    echo();
    curs_set(1);
    
    char ssid_buf[64] = {0};
    wgetstr(wifi_menu, ssid_buf);       // reads input, Enter to confirm
    std::string ssid(ssid_buf);


    mvwprintw(wifi_menu,2,1,"Password: ");
    wrefresh(wifi_menu);

    char pswd_buf[64] = {0};
    wgetstr(wifi_menu, pswd_buf);       // reads input, Enter to confirm
    std::string password(pswd_buf);

       // Connect
    std::string cmd = "nmcli device wifi connect \"" + ssid + "\" password \"" + password + "\" > /dev/null 2>&1";
    int ret = system(cmd.c_str());
    refresh();
    curs_set(0);
    noecho();
    if(ret == 0)
    {
        wattron(wifi_menu, COLOR_PAIR(1));
        mvwprintw(wifi_menu, 4, 1, "Connected successfully!");
        wattroff(wifi_menu, COLOR_PAIR(1));
    }
    else
    {
        wattron(wifi_menu, COLOR_PAIR(2));
        mvwprintw(wifi_menu, 4, 1, "Failed to connect.");
        wattroff(wifi_menu, COLOR_PAIR(2));
    }

    wrefresh(wifi_menu);
    getch();
    machine = state::WIFI_MAIN;

    werase(wifi_menu);
        
}

void display_wifi_status(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
    int key;
    // static WINDOW * wifi_home = newwin(5,   w, line_start, space_start);
    // static WINDOW * wifi_status = newwin(3, w, line_start+4, space_start);
    static WINDOW * wifi_menu = newwin(h-6, w, 6, space_start);
    wbkgd(wifi_menu, COLOR_PAIR(0));

    // refresh();
    
    // wattron(wifi_home,A_BOLD);
    // print_centered(wifi_home, 2, w, "WiFi Control");

    // box(wifi_home, 0, 0);
    // wborder(wifi_status,0,0,0,0,'+','+','+','+'); 
    wborder(wifi_menu,0,0,0,0,'+','+',0,0); 


    // wrefresh(wifi_home);
    wrefresh(wifi_menu);
    // wrefresh(wifi_status);

    mvwprintw(wifi_menu, 1, 2, "State    : %s", cmd_output("nmcli radio wifi").c_str());
    mvwprintw(wifi_menu, 2, 2, "IP       : %s", cmd_output("hostname -I").c_str());
    mvwprintw(wifi_menu, 3, 2, "MAC      : %s", cmd_output("cat /sys/class/net/wlp0s20f3/address").c_str());
    mvwprintw(wifi_menu, 4, 2, "Details  : %s", cmd_output("nmcli -t -f ACTIVE,SSID,SIGNAL,SECURITY dev wifi | grep '^yes'").c_str());

    mvwprintw(wifi_menu, 6, 2, "Press any key to go back...");

    wrefresh(wifi_menu);
    getch();

    machine = state::WIFI_MAIN;
    wclear(wifi_menu);
    wrefresh(wifi_menu);
}

void remove_network(void)
{
    int h, w, line_start, space_start;
    h=7*4-3;
    w=80;
    line_start =0;
    space_start =0;
    int key;
    static WINDOW * wifi_menu = newwin(h-6, w, 6, space_start);
    wbkgd(wifi_menu, COLOR_PAIR(0));


    wborder(wifi_menu,0,0,0,0,'+','+',0,0); 

   
    wrefresh(wifi_menu);
    

    

    mvwprintw(wifi_menu,1,1,"Network Name that you want to remove: ");
    wrefresh(wifi_menu);

    wmove(wifi_menu,2,1);
    wrefresh(wifi_menu);
    
    echo();
    curs_set(1);
    
    
    char ssid_buf[64] = {0};
    wgetstr(wifi_menu, ssid_buf);       // reads input, Enter to confirm
    std::string ssid(ssid_buf);

       // Connect
    std::string cmd = "nmcli connection delete \"" + ssid + "\" > /dev/null 2>&1";
    int ret = system(cmd.c_str());

    refresh();
    curs_set(0);
    noecho();
    if(ret == 0)
    {
        wattron(wifi_menu, COLOR_PAIR(1));
        mvwprintw(wifi_menu, 4, 1, "Network removed successfully!");
        wattroff(wifi_menu, COLOR_PAIR(1));
    }
    else
    {
        wattron(wifi_menu, COLOR_PAIR(2));
        mvwprintw(wifi_menu, 4, 1, "Could not find the Network.");
        wattroff(wifi_menu, COLOR_PAIR(2));
    }

    wrefresh(wifi_menu);
    getch();
    machine = state::WIFI_MAIN;

    werase(wifi_menu);
        
}

void modify_network(void)
{
    int h=7*4-3, w=80;
    static WINDOW* wifi_menu = newwin(h-6, w, 6, 0);

    wbkgd(wifi_menu, COLOR_PAIR(0));
    wborder(wifi_menu,0,0,0,0,'+','+',0,0);

    mvwprintw(wifi_menu, 1, 1, "Network Name that you want to modify: ");
    wmove(wifi_menu, 2, 1);
    wrefresh(wifi_menu);

    echo();
    curs_set(1);

    char ssid_buf[64] = {0};
    wgetstr(wifi_menu, ssid_buf);
    std::string ssid(ssid_buf);

    mvwprintw(wifi_menu, 3, 1, "New Password: ");
    wmove(wifi_menu, 4, 1);
    wrefresh(wifi_menu);

    char pass_buf[64] = {0};
    wgetstr(wifi_menu, pass_buf);
    std::string new_password(pass_buf);

    curs_set(0);
    noecho();

    // Modify password
    std::string cmd = "nmcli connection modify \"" + ssid + "\" wifi-sec.psk \"" + new_password + "\" > /dev/null 2>&1";
    int ret = system(cmd.c_str());
    refresh();

    // Reconnect to apply
    if(ret == 0)
    {
        std::string cmd2 = "nmcli connection up \"" + ssid + "\" > /dev/null 2>&1";
        system(cmd2.c_str());
        refresh();

        wattron(wifi_menu, COLOR_PAIR(1));
        mvwprintw(wifi_menu, 6, 1, "Network modified successfully!");
        wattroff(wifi_menu, COLOR_PAIR(1));
    }
    else
    {
        wattron(wifi_menu, COLOR_PAIR(2));
        mvwprintw(wifi_menu, 6, 1, "Could not find the Network.");
        wattroff(wifi_menu, COLOR_PAIR(2));
    }

    wrefresh(wifi_menu);
    getch();

    machine = state::WIFI_MAIN;
    werase(wifi_menu);
    wrefresh(wifi_menu);
}

void search_for_network(void)
{
    int h=7*4-3, w=80;
    static WINDOW* wifi_home = newwin(5,   w, 0, 0);
    static WINDOW* wifi_menu = newwin(h-4, w, 4, 0);

    wbkgd(wifi_menu, COLOR_PAIR(0));
    box(wifi_home, 0, 0);
    wborder(wifi_menu,0,0,0,0,'+','+',0,0);

    wattron(wifi_home, A_BOLD);
    print_centered(wifi_home, 2, w, "Search for a Network");
    wattroff(wifi_home, A_BOLD);

    wrefresh(wifi_home);

    // Scan and get available networks
    mvwprintw(wifi_menu, 1, 1, "Scanning...");
    wrefresh(wifi_menu);

    std::string result = cmd_output("nmcli -t -f SSID,SIGNAL,SECURITY dev wifi list");

    // Display results
    werase(wifi_menu);
    wborder(wifi_menu,0,0,0,0,'+','+',0,0);

    if(result.empty())
    {
        wattron(wifi_menu, COLOR_PAIR(2));
        mvwprintw(wifi_menu, 1, 1, "No networks found.");
        wattroff(wifi_menu, COLOR_PAIR(2));
    }
    else
    {
        mvwprintw(wifi_menu, 1, 1, "%-30s %-10s %-10s", "SSID", "SIGNAL", "SECURITY");
        mvwprintw(wifi_menu, 2, 1, "%-50s", "──────────────────────────────────────────────────");

        // Parse and print each line
        std::istringstream ss(result);
        std::string line;
        int row = 3;
        while(std::getline(ss, line) && row < h-6)
        {
            // format is SSID:SIGNAL:SECURITY
            std::string ssid     = line.substr(0, line.find(':'));
            line = line.substr(line.find(':')+1);
            std::string signal   = line.substr(0, line.find(':'));
            std::string security = line.substr(line.find(':')+1);

            mvwprintw(wifi_menu, row, 1, "%-30s %-10s %-10s",
                ssid.c_str(), (signal+"%").c_str(), security.c_str());
            row++;
        }
    }

    mvwprintw(wifi_menu, h-8, 1, "Press any key to go back...");
    wrefresh(wifi_menu);
    getch();

    machine = state::WIFI_MAIN;
    werase(wifi_home); wrefresh(wifi_home);
    werase(wifi_menu); wrefresh(wifi_menu);
}