/*******************************************************************************
** Program: zooDirector
** File:    Tiger.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Tiger derived class. It
** inherits from the Animal class.
*******************************************************************************/

#ifndef TIGER_HPP
#define TIGER_HPP

#include "Animal.hpp"

class Tiger : public Animal {
public:
	Tiger(int foodCost, int age = 0);
    int getAge(),
        getCost(),
        getFoodCost(),
        getNumBabies(),
        getPayoff();
    void oneDayOlder();
};

#endif