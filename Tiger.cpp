/*******************************************************************************
** Program: zooDirector
** File:    Tiger.cpp
** -----------------------------------------------------------------------------
** This is the implementation file for the Tiger derived class. It inherits from
** the Animal class.
*******************************************************************************/

#include "Tiger.hpp"

/*
** Constructor for the Tiger class.
*/
Tiger::Tiger(int foodCost, int age) {
	this->age = age;
	this->cost = 10000;
	this->foodCost = foodCost * 5;
    this->numBabies = 1;
	this->payoff = 2000;
}

/*
** Getters (accessors) for Tiger class.
*/
int Tiger::getAge() {
    return this->age;
}

int Tiger::getCost() {
    return this->cost;
}

int Tiger::getFoodCost() {
    return this->foodCost;
}

int Tiger::getNumBabies() {
    return this->numBabies;
}

int Tiger::getPayoff() {
    return this->payoff;
}

/*
** Increases age of Tiger by one.
*/
void Tiger::oneDayOlder() {
    this->age++;
}