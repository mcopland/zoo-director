/*******************************************************************************
** Program: zooDirector
** File:    Penguin.cpp
** -----------------------------------------------------------------------------
** This is the implementation file for the Penguin derived class. It inherits
** from the Animal class.
*******************************************************************************/

#include "Penguin.hpp"

/*
** Constructor for Penguin class.
*/
Penguin::Penguin(int foodCost, int age) {
	this->age = age;
	this->cost = 1000;
	this->foodCost = foodCost;
    this->numBabies = 5;
	this->payoff = 100;
}

/*
** Getters (accessors) for Penguin class.
*/
int Penguin::getAge() {
    return this->age;
}

int Penguin::getCost() {
    return this->cost;
}

int Penguin::getFoodCost() {
    return this->foodCost;
}

int Penguin::getNumBabies() {
    return this->numBabies;
}

int Penguin::getPayoff() {
    return this->payoff;
}

/*
** Increases age of Penguin by one.
*/
void Penguin::oneDayOlder() {
    this->age++;
}