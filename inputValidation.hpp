/*******************************************************************************
** Program: zooDirector
** File:    inputValidation.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the inputValidation functions.
** There are two functions within: one to check for a valid int within a set
** range and another to check for a valid yes or no selection.
*******************************************************************************/

#ifndef INPUT_VALIDATION_HPP
#define INPUT_VALIDATION_HPP

#include <iostream>
#include <sstream>

int getValidIntInRange(int min, int max);
char getValidYesNo(); 

#endif