#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

int main()
{
    // std::string result = system("nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes'");
    // std::cout << result << std::endl;

    const char* cmd = "nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes' ";
    
    std::string result;
    char buffer[128];

    // Open pipe to read command output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return 1;
    }

    // Read output into result
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // Remove trailing newline
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    std::cout << "Connected SSID: " << result << std::endl;

    return 0;
}