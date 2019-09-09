/*******************************************************************************
** Program: zooDirector
** File:    Turtle.cpp
** -----------------------------------------------------------------------------
** This is the implementation file for the Turtle derived class. It inherits
** from the Animal class.
*******************************************************************************/

#include "Turtle.hpp"

/*
** Constructor for the Turtle class.
*/
Turtle::Turtle(int foodCost, int age) {
	this->age = age;
	this->cost = 100;
	this->foodCost = foodCost / 2;
    this->numBabies = 10;
	this->payoff = 5;
}

/*
** Getters (accessors) for Turtle class.
*/
int Turtle::getAge() {
    return this->age;
}

int Turtle::getCost() {
    return this->cost;
}

int Turtle::getFoodCost() {
    return this->foodCost;
}

int Turtle::getNumBabies() {
    return this->numBabies;
}

int Turtle::getPayoff() {
    return this->payoff;
}

/*
** Increases age of Penguin by one.
*/
void Turtle::oneDayOlder() {
    this->age++;
}