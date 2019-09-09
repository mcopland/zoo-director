/*******************************************************************************
** Program: zooDirector
** File:    main.cpp
** -----------------------------------------------------------------------------
** This is the zooDirector main file. A Menu and Game are created, then the
** program is looped until the user decides to quit.
*******************************************************************************/

#include "inputValidation.hpp"
#include "Menu.hpp"
#include "Zoo.hpp"

#include <cstdlib>      // srand
#include <ctime>        // time
#include <iostream>     // cout, endl
#include <string>       // string

int main() {
    using std::cout;
    using std::endl;

	// seed for RNG
	srand(static_cast<unsigned>(std::time(0)));

    bool programExit = false;
	char userMenuChoice;
    Zoo newGame;

    // create a menu and add options
    Menu zooMenu;
    zooMenu.addOption("Play Zoo Tycoon");
    zooMenu.addOption("Exit program");

    // loop program until the user terminates
    while (!programExit) {
        zooMenu.printMenu();
		cout << "\nSelect an option: ";
		userMenuChoice = getValidIntInRange(1, 2);

        // start processes based on user choice
        switch (userMenuChoice) {
            case 1:
				newGame.playGame();
                break;
            case 2:
                programExit = true;
                break;
            default:
                break;
        }
    }

    return 0;
}