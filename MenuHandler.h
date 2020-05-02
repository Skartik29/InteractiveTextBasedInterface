#pragma once
#include <iostream>
#include <cstring>

namespace MENUHANDLINGUTILITY
{
    enum class MenuOptions
    {
        NEXTLINE = 0,
        SEARCH,
        REPLACE,
        INPUTFROM,
        READFILE,
        WRITETO,
        WRITEFILE,
        LOADOPTIONS,
        END
    };

    std::string MenuHandler(const MenuOptions& mode)
    {
        switch (mode)
        {
            case MenuOptions::NEXTLINE:
            {
                return "Enter next line in the input\n";
            }
            case MenuOptions::SEARCH:
            {
                return "Enter the key to search\n";
            }
            case MenuOptions::REPLACE:
            {
                return "Enter the key to replace with\n";
            }
            case MenuOptions::INPUTFROM:
            {
                return "Input from a file (1) or console (2)";
            }
            case MenuOptions::READFILE:
            {
                return "Enter the filename to read from with extension\n";
            }
            case MenuOptions::WRITETO:
            {
                return "Write to a file (1) or to console (2)";
            }
            case MenuOptions::WRITEFILE:
            {
                return "Enter the filename to write with extension\n";
            }
            case MenuOptions::LOADOPTIONS:
            {
                return  "Enter (1) to load previous data and anything else to write from scratch\n";
            }
            default:
            {
                return "";
            }
        }
    }
}