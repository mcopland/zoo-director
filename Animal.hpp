/*******************************************************************************
** Program: zooDirector
** File:    Animal.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Animal abstract class. It is
** the base for the Penguin, Tiger, and Turtle classes.
*******************************************************************************/

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal {
protected:
    int age,
        cost,
        foodCost,
        numBabies,
        payoff;
public:
	Animal();
	~Animal();

	// virtual functions
	virtual int getAge() = 0;
	virtual int getCost() = 0;
	virtual int getFoodCost() = 0;
    virtual int getNumBabies() = 0;
	virtual int getPayoff() = 0;
	virtual void oneDayOlder() = 0;
};

#endif