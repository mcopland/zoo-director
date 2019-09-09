/*******************************************************************************
** Program: zooDirector
** File:    Zoo.cpp
** -----------------------------------------------------------------------------
** This is the implementation file for the Zoo class. The player begins with a
** specific amount of money in the bank and needs to buy three types of Animals.
** Each turn is a day. All Animals increase their age, feeding costs are
** deducted, and a random event occurs.
*******************************************************************************/

#include "inputValidation.hpp"
#include "Menu.hpp"
#include "Penguin.hpp"
#include "Tiger.hpp"
#include "Turtle.hpp"
#include "Zoo.hpp"

#include <iostream>

/*
* Default constructor for the Zoo class.
*/
Zoo::Zoo() {}

/**
* The main function of the Zoo class. Runs the game.
*/
void Zoo::playGame() {
	using std::cin;
	using std::cout;
	using std::endl;

	// constants
	const int ADULT_AGE = 3;
	const int BASE_FOOD_COST = 10;
	const int NUM_OF_SPECIES = 3;
	const int START_ANIMALS_MAX = 2;
	const int START_ANIMALS_MIN = 1;
	const int STARTING_CAPACITY = 10;
	
	Animal* animalPtr;
	AnimalSpecies typeToBuy;
	bool animalAdded, cancel;
	char choice;
	int eventNum, startingAnimals;

	// initialize beginning
	bank = 100000;
	currentDay = 0;
	numSpecies = NUM_OF_SPECIES;
		
	// allocate memory
	animals = new Animal**[NUM_OF_SPECIES];
	numAnimals = new int[NUM_OF_SPECIES];
	quantity = new int[NUM_OF_SPECIES];
	shuffledTypes = new int[NUM_OF_SPECIES];

	for (int i = 0; i < NUM_OF_SPECIES; ++i) {
		animals[i] = new Animal*[STARTING_CAPACITY];
		numAnimals[i] = 0;
		quantity[i] = STARTING_CAPACITY;
		shuffledTypes[i] = i;

		for (int j = 0; j < STARTING_CAPACITY; ++j) {
			animals[i][j] = nullptr;
		}
	}

////////// print instructions
		cout << "\nStarting bank: $100,000\n"
			 << "In order to begin, you must first buy 1 or 2 of each animal.\n";

////////// buy Tiger
		typeToBuy = TIGER;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);
		cout << "\nHow many Tigers would you like to buy?\n";
		startingAnimals = getValidIntInRange(START_ANIMALS_MIN, START_ANIMALS_MAX);

		for (int i = startingAnimals; i > 0; --i) {
			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			bank -= animalPtr->getCost();
		}

////////// buy Penguin
		typeToBuy = PENGUIN;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);
		cout << "\nHow many Penguins would you like to buy?\n";
		startingAnimals = getValidIntInRange(START_ANIMALS_MIN, START_ANIMALS_MAX);

		for (int i = startingAnimals; i > 0; --i) {
			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			bank -= animalPtr->getCost();
		}

////////// buy Turtle
		typeToBuy = TURTLE;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);
		cout << "\nHow many Turtles would you like to buy?\n";
		startingAnimals = getValidIntInRange(START_ANIMALS_MIN, START_ANIMALS_MAX);

		for (int i = startingAnimals; i > 0; --i) {
			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			bank -= animalPtr->getCost();
		}

////////// start game
		do {
		////// beginning
			currentDay++;
			ageAllAnimals();
			feedingCost = 0;
			payoff = 0;
			bonus = 0;

			printDayBegin();

		////// pay daily costs
			payFeedingCost();
			printCosts();

		////// random event
			eventNum = rand() % 4;
			eventName = static_cast<RandomEvent>(eventNum);

			switch (eventName) {
			case SICKNESS:
				eventSickness();
				break;
			case BOOM:
				eventBoom(250, 500);
				break;
			case BIRTH:
				eventBorn(ADULT_AGE, BASE_FOOD_COST);
				break;
			case NOTHING:
				break;
			}

			printRandomEvent();

		////// profit
			calcProfits();
			printProfits();

		////// buy new animal
			cout << "\nWould you like to buy an adult Animal (y/n)?\n";
			choice = getValidYesNo();

			if (choice == 'y') {
				animalAdded = false;
				cancel = false;
				do {
					cout << "\nWhich Animal would you like to buy:\n";
					cout << "\n1) Tiger\n"
						<< "2) Penguin\n"
						<< "3) Turtle\n"
						<< "4) Cancel\n";

					cout << "Enter your selection: ";
					choice = getValidIntInRange(1, 4);

					switch (choice) {
					case 1:
						typeToBuy = TIGER;
						break;
					case 2:
						typeToBuy = PENGUIN;
						break;
					case 3:
						typeToBuy = TURTLE;
						break;
					case 4:
						cancel = true;
						break;
					}

					if (cancel == false) {

						printAnimalInfo(typeToBuy, BASE_FOOD_COST);
						createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST, ADULT_AGE);

						// check for insufficient funds
						if (animalPtr->getCost() > bank) {
							cout << "\nNot enough money in the bank.";

							delete animalPtr;
							animalPtr = nullptr;
							cancel = true;
						}
						else {
							addAnimal(typeToBuy, &animalPtr);
							bank -= animalPtr->getCost();
							animalAdded = true;
						}
					}

				} while (animalAdded == false && cancel == false);
			}

		////// end of day
			printDayEnd();

		////// check for end of game
			if (bank < 0) {
				cout << "\nYou ran out of money!\n"
					 << "GAME OVER\n" << endl;
				choice = 2;
			}
			else {
				cout << "1) Keep playing\n"
					 << "2) Go back to Menu\n";
				choice = getValidIntInRange(1, 2);
			}

		} while (choice != 2);

////////// game over

		// clean up
		for (int i = 0; i < numSpecies; ++i) {
			for (int j = 0; j < numAnimals[i]; ++j) {
				delete animals[i][j];
			}

			delete[] animals[i];
		}

		delete[] animals;
		delete[] quantity;
		delete[] numAnimals;
		delete[] shuffledTypes;

		cout << endl;
}

/*
** Adds Animal if possible. If there is no more space, the capacity is
** doubled and the Animal is added.
*/
void Zoo::addAnimal(AnimalSpecies type, Animal** animalPtr) {
	bool animalAdded = false;
	int animal = 0;

	// check for space in array
	while (!animalAdded && animal < quantity[type]) {

		// stop looping once a spot is located
		if (animals[type][animal] == nullptr) {

			animals[type][animal] = *animalPtr;
			animalAdded = true;
		}

		animal++;
	}

	// if the animal was not added, then the array was full.
	if (animalAdded == false) {
		int newQuantity = quantity[type] * 2;
		Animal** tempArray = new Animal*[newQuantity];
		
		for (int i = 0; i < quantity[type]; ++i) {
			tempArray[i] = animals[type][i];
		}
		
		delete[] animals[type];

		// initialize to null
		for (int i = quantity[type]; i < newQuantity; ++i) {
			tempArray[i] = nullptr;
		}

		// set previous array to new array
		animals[type] = tempArray;

		// add Animal to first open space in array.
		animals[type][quantity[type]] = *animalPtr;
		animalAdded = true;

		// new capacity
		quantity[type] = newQuantity;
	}

	numAnimals[type]++;
}

/*
** Iterates through all existing Animal objects and ages them by one day.
*/
void Zoo::ageAllAnimals() {

	// Loop through each animal type.
	for (int i = 0; i < numSpecies; ++i) {

		// Loop through each animal of the given type if there are any
		// until an empty space is encountered.
		for (int j = 0; j < numAnimals[i]; ++j) {

			// Increment the age of the animal.
			animals[i][j]->oneDayOlder();
		}
	}
}

/*
** Calculates profits for each day.
*/
void Zoo::calcProfits() {
	int dailyProfit = 0;

	// add payoff for each existing Animal
	for (int i = TIGER; i < numSpecies; ++i) {

		// one Animal must exist
		if (numAnimals[i] != 0 && animals[i][0] != nullptr) {

			// take payoff
			dailyProfit = animals[i][0]->getPayoff();

			// multiply it by the number of animals of this species
			dailyProfit *= numAnimals[i];

			payoff += dailyProfit;
		}
	}

	bank += payoff;
	bank += bonus;
}

/*
** Creates an Animal object based on selected type.
*/
void Zoo::createAnimal(AnimalSpecies type, Animal** animalPtr, int foodCost, int age) {
	switch (type) {
	case TIGER:
		*animalPtr = new Tiger(foodCost, age);
		break;
	case PENGUIN:
		*animalPtr = new Penguin(foodCost, age);
		break;
	case TURTLE:
		*animalPtr = new Turtle(foodCost, age);
		break;
	}
}

/*
** Random event where a boom in attendance leads to a bonus for that day.
*/
void Zoo::eventBoom(int minBonus, int maxBonus) {
	// check for Tigers in Zoo
	if (numAnimals[TIGER] != 0 && animals[TIGER][0] != nullptr) {

		bonus = minBonus + (rand() % (maxBonus - minBonus + 1));

		// multiply by number of tigers in the Zoo
		bonus *= numAnimals[TIGER];
	}
	else {
		eventName = NOTHING;
	}
}

/*
** Random event where a baby Animal is born. Adds another Animal to
** array of given species.
*/
void Zoo::eventBorn(int adultAge, int foodCost) {
	Animal* animalPtr = nullptr;
	bool animalsBorn = false;
	int type = 0;				// animal species index
	int animal = 0;				// animal index

	while (animalsBorn == false && type < numSpecies) {
		randomType = static_cast<AnimalSpecies>(shuffledTypes[type]);

		// must have at least one animal
		if (numAnimals[randomType] != 0 && animals[randomType][0] != nullptr) {
			
			// check for adults
			while (animalsBorn == false && animal < numAnimals[randomType]) {
				if (animals[randomType][animal]->getAge() >= adultAge) {
					int numBabies = animals[randomType][0]->getNumBabies();
					
					// create and add animals
					for (int i = 0; i < numBabies; ++i) {
						createAnimal(randomType, &animalPtr, foodCost);
						addAnimal(randomType, &animalPtr);
					}

					animalsBorn = true;
				}

				animal++;
			}
		}

		type++;
	}

	if (animalsBorn == false) {
		eventName = NOTHING;
	}
}

/*
** Event where an Animal becomes sick and dies. The Animal is then
** removed from the dynamic array.
*/
void Zoo::eventSickness() {
	bool animalRemoved = false;
	int speciesTemp = 0;
	
	while (animalRemoved == false && speciesTemp < numSpecies) {
		randomType = static_cast<AnimalSpecies>(shuffledTypes[speciesTemp]);

		// check for at least one count of Animal
		if (numAnimals[randomType] != 0 && animals[randomType][0] != nullptr) {

			// select random Animal
			int animal = rand() % numAnimals[randomType];

			// remove Animal
			delete animals[randomType][animal];
			animals[randomType][animal] = nullptr;

			// shift to cover empty spot
			for (int j = animal; j < numAnimals[randomType] - 1; ++j) {
				animals[randomType][j] = animals[randomType][j + 1];
			}

			// set last element to null, decrement animal count
			animals[randomType][numAnimals[randomType] - 1] = nullptr;
			numAnimals[randomType]--;

			animalRemoved = true;
		}

		speciesTemp++;
	}

	if (animalRemoved == false) {
		
		eventName = NOTHING;	
	}
}

/*
** Calculates total food cost of the day.
*/
void Zoo::payFeedingCost() {
	int speciesCost = 0;

	// add up feed cost for each animal
	for (int i = TIGER; i < numSpecies; ++i) {
		if (numAnimals[i] != 0 && animals[i][0] != nullptr) {
			// get food cost
			speciesCost = animals[i][0]->getFoodCost();

			// multiply by the current number of animals
			speciesCost *= numAnimals[i];

			// add cost to daily total
			feedingCost += speciesCost;
		}
	}

	// subtract total cost from player's bank
	bank -= feedingCost;
}

/*
** Prints information of a given animal.
*/
void Zoo::printAnimalInfo(AnimalSpecies species, int foodCost) {
	using std::cout;
	using std::endl;

	Animal* tempAnimal = nullptr;
	std::string speciesStr = "";	// holds an indicator of species

	switch (species) {
	case TIGER:
		tempAnimal = new Tiger(foodCost);
		speciesStr = "***** Tiger Information *****";
		break;
	case PENGUIN:
		tempAnimal = new Penguin(foodCost);
		speciesStr = "***** Penguin Information *****";
		break;
	case TURTLE:
		tempAnimal = new Turtle(foodCost);
		speciesStr = "***** Turtle Information *****";
		break;
	}

	cout << endl << speciesStr << endl
		 << "Cost:       $" << tempAnimal->getCost() << endl
		 << "Food Cost:  $" << tempAnimal->getFoodCost() << endl
		 << "Payoff:     $" << tempAnimal->getPayoff() << endl
		 << "# of Babies: " << tempAnimal->getNumBabies() << endl;

	// deallocate memory
	delete tempAnimal;
	tempAnimal = nullptr;
}

/*
** Prints daily costs.
*/
void Zoo::printCosts() {
	using std::cout;
	using std::endl;

	cout << "\n Today's Costs\n"
		 << "---------------\n"
		 << " Feed cost:    " << feedingCost << endl
		 << " Updated bank: " << bank << endl;
}

/*
** Prints the player's bank and the quantity of each animal.
*/
void Zoo::printDayBegin() {
	using std::cout;
	using std::endl;

	cout << "\n Beginning of Day " << currentDay << endl
		 << "--------------------\n"
		 << " # of Tigers:    " << numAnimals[TIGER] << endl
		 << " # of Penguins:  " << numAnimals[PENGUIN] << endl
		 << " # of Turtles:   " << numAnimals[TURTLE] << endl
		 << " Starting bank: $" << bank << endl;
}

/*
** Prints results at the end of the day.
*/
void Zoo::printDayEnd() {
	using std::cout;
	using std::endl;

	// Print day title row.
	cout << "\n End of Day " << currentDay << endl
		 << "--------------\n";

	cout << " # of Tigers:   " << numAnimals[TIGER] << endl;
	cout << " # of Penguins: " << numAnimals[PENGUIN] << endl;
	cout << " # of Turtles:  " << numAnimals[TURTLE] << endl;
	cout << " Ending bank:  $" << bank << endl << endl;
}

/*
** Prints daily profits.
*/
void Zoo::printProfits() {
	using std::cout;
	using std::endl;
	
	cout << "\n Today's Profits" << endl
		<< "-----------------\n";

	// print payoff
	cout << "Today's Payoff: $" << payoff << endl;

	// print bonus
	cout << "Event Bonus:    $" << bonus << endl;

	// print bank
	cout << "Updated bank:   $" << bank << endl;
}

/*
** Print message for a random event.
*/
void Zoo::printRandomEvent() {
	using std::cout;
	using std::endl;

	std::string species = "",
			    eventMsg = "";

	// get animal the event happened to
	switch (randomType) {
	case TIGER:
		species = "tiger";
		break;
	case PENGUIN:
		species = "penguin";
		break;
	case TURTLE:
		species = "turtle";
	}

	// get message for the event
	switch (eventName) {
	case SICKNESS:
		eventMsg = " Sadly, a " + species + " passed away today.";
		break;
	case BOOM:
		eventMsg = " A boom in attendance occured! Expect a bonus!";
		break;
	case BIRTH:
		eventMsg = " Congratulations! A " + species + " gave birth today!";
		break;
	case NOTHING:
		eventMsg = " Nothing happened today.";
		break;
	}

	// print random event
	cout << "\n Random Event\n" << "--------------\n " << eventMsg << endl;
}