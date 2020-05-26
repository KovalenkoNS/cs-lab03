#include <windows.h>
#include <sstream>
#include <iostream>
#include <string>
#include "system_info.h"
using namespace std;
string make_info_text()
{
    stringstream buffer;
    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;

    if ((info & 0x40000000) == 0)
        {
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    }

    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    buffer << "Computer name: " << computer_name << "\n";

    return buffer.str();
}

