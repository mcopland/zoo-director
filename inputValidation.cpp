/*******************************************************************************
** Program: zooDirector
** File:    inputValidation.cpp
** -----------------------------------------------------------------------------
** This is the implementation file for the inputValidation functions. There are
** two functions within: one to check for a valid int within a set range and
** another to check for a valid yes or no selection.
*******************************************************************************/

#include "inputValidation.hpp"

/*
** Validates user input for an int value between a set range.
*/
int getValidIntInRange(int min, int max) {
    using std::cout;
    using std::cin;
    using std::endl;

	bool validEntry = false;
	int validInt;
	std::string input;

	while (!validEntry) {
		getline(cin, input);
		std::stringstream userStream(input);

		if (userStream >> validInt && !(userStream >> input)) {
			
			// check if valid
			if (validInt < min || validInt > max) {
				cout << "\nEnter an integer between " << min << " and "
					 << max << ". " << endl;
			}
			else {
				validEntry = true;
			}
		}
		else {
			cout << "\nEnter an integer between " << min << " and "
				 << max << "." << endl;
		}
	}

	return validInt;
}

/*
** Validates user input for a valid yes or no selection.
*/
char getValidYesNo() {
    using std::cout;
    using std::cin;
    using std::endl;

	bool validSelection = false;
	char validChar;
	std::string input;
	
	while (!validSelection) {
		getline(cin, input);
		std::stringstream sStream(input);

		if (sStream >> validChar && !(sStream >> input)) {

			// check if valid
			if (validChar != 'Y' && validChar != 'y' &&
				validChar != 'N' && validChar != 'n') {

				cout << "\nEnter either (y\\Y) or (n\\N)" << endl;
			}
			else {

				validSelection = true;
			}
		}
		else {
			cout << "\nEnter either (y\\Y) or (n\\N)" << endl;
		}
	}

	return validChar;
}