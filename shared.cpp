#include "shared.hpp"


void print_centered(WINDOW *win, int row, int w, const char *text) {
    int x = (w - (int)strlen(text)) / 2;
    if (x < 1) x = 1; // prevent overflow into border
    mvwprintw(win, row, x, text);
}

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