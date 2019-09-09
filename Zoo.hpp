/*******************************************************************************
** Program: zooDirector
** File:    Zoo.hpp
** -----------------------------------------------------------------------------
** This is the specification (header) file for the Zoo class. The player begins
** with a specific amount of money in the bank and needs to buy three types of
** Animals. Each turn is a day. All Animals increase their age, feeding costs
** are deducted, and a random event occurs.
*******************************************************************************/

#ifndef ZOO_HPP
#define ZOO_HPP

#include "Animal.hpp"

enum AnimalSpecies { TIGER, PENGUIN, TURTLE };
enum RandomEvent { SICKNESS, BOOM, BIRTH, NOTHING };

class Zoo {
private:
	Animal*** animals;
	int* quantity;			// tracks the capacity of each array
	int* numAnimals;
	int* shuffledTypes;		// holds an index of species to shuffle

	AnimalSpecies randomType;
	RandomEvent eventName;

	int bank,
		bonus,
		currentDay,
		feedingCost,
		numSpecies,
		payoff;
	
	void addAnimal(AnimalSpecies type, Animal** animal),
		ageAllAnimals(),
		calcProfits(),
		createAnimal(AnimalSpecies type, Animal** animal, int foodCost, int age = 1),
		eventBoom(int minBonus, int maxBonus),
		eventBorn(int adultAge, int foodCost),
		eventSickness(),
		payFeedingCost();

	// print functions
	void printAnimalInfo(AnimalSpecies type, int foodCost),
		 printCosts(),
		 printDayBegin(),
		 printDayEnd(),
		 printProfits(),
		 printRandomEvent();

public:
	Zoo();
	void playGame();
};

#endif