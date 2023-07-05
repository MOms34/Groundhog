/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "../../include/Groundhog.hpp"
#include "../../include/IGroundhog.hpp"

void display_help(void)
{
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "    " << "./groundhog" << " period\n" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "    period\tthe number of days defining a period" << std::endl;
}

bool isNonNegativeNumber(const std::string& str)
{
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
        if (c == '0' && str.size() > 1) {
            return false;
        }
    }
    return true;
}

int main(int ac, char **argv)
{
    std::string help = "-h";

    if (ac != 2) {
        std::cerr << " Invalid argument." << std::endl;
        display_help();
        return ERROR;
    }
    if (strcmp(argv[1], help.c_str()) == 0) {
        display_help();
        return SUCCESS;
    }
    std::string arg(argv[1]);
    if (isNonNegativeNumber(arg) == false) {
        std::cerr << " Invalid argument, it must be a number positive." << std::endl;
        display_help();
        return ERROR;
    }
    Groundhog g(std::atoi(argv[1]));
    g.loop();

    return 0;
}