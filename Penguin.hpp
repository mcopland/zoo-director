/*******************************************************************************
** Program: zooDirector
** File:    Penguin.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Penguin derived class. It
** inherits from the Animal class.
*******************************************************************************/

#ifndef PENGUIN_HPP
#define PENGUIN_HPP

#include "Animal.hpp"

class Penguin : public Animal {
public:
	Penguin(int foodCost, int age = 0);
    int getAge(),
        getCost(),
        getFoodCost(),
        getNumBabies(),
        getPayoff();
    void oneDayOlder();
};

#endif