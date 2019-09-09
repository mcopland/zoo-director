/*******************************************************************************
** Program: zooDirector
** File:    Menu.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Menu class. The Menu is
** modular, allowing multiple options to be added from the main file.
*******************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>

class Menu {
private:
    std::vector<std::string> menuOptions;
public:
    Menu();
    int getMenuSize();
    void addOption(std::string prompt),
         printMenu();
};

#endif