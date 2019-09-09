/*******************************************************************************
** Program: zooDirector
** File:    Turtle.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Turtle derived class. It
** inherits from the Animal class.
*******************************************************************************/

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "Animal.hpp"

class Turtle : public Animal {
public:
	Turtle(int foodCost, int age = 0 );
    int getAge(),
        getCost(),
        getFoodCost(),
        getNumBabies(),
        getPayoff();
    void oneDayOlder();
};

#endif