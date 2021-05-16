#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "UtilFunctions.h"
#include "Screen.h"
#include "StringReference.h"
#include "Map.h"

//Could be private class member variables. Not sure if I can use classes for this assignment
int room = 5;
int turnCounter = 0;
int crewmateCount = 5;
int susMeter = 10;
int health = 100;
const int maxHealth = 100;

void mapScreen()
{
	
	while (true)
	{
		//Prints out the ASCII map
		std::cout << StringRef::mapEmpty;

		//Displays player stats on the right
		setConsoleCursorPos(65, 0);
		std::cout << "Sus: " << susMeter;
		setConsoleCursorPos(65, 1);
		std::cout << "Room: " << room;

		//Check if 5 turnes have passed to call an emergency meeting
		if (turnCounter == 5)
		{
			emergencyMeeting();
		}

		//Asks the user what they want to do
		setConsoleCursorPos(1, 25);
		std::cout << "Select options: (1)Move room (2)Do task (3)Fight (if other crewmates are in the same room) (4)Do nothing";
		int option = getPlayerOption(1, 4);
		if (option == 1)
		{
			room = roomSelector();
		}
		else if (option == 2)
		{
			susMeter = doTask(susMeter);
		}
		susMeter = susMeter + 10;
	}
}

int roomSelector()
{
	setConsoleCursorPos(0, 25);
	std::cout << "\033[2K";
	std::cout << "What room would you like to move to (Room 1 is on the top left. Rooms are ordered left to right, top to bottom)";
	int room = getPlayerOption(1, 9);
	return room;
	
	return 1;
}

//Tasks are multiplication questions because I didn't know how to implement tasks
int doTask(int sus)
{
	int or1 = getRandomNumber(0, 12);
	int or2 = getRandomNumber(0, 12);
	setConsoleCursorPos(0, 25);
	std::cout << "\033[2K";
	std::cout << "What is the answer to " << or1 << " * " << or2 << '?';
	int answer = getNumInput();

	if (answer == or1 * or2)
	{
		sus = sus - 20;
		if (sus < 0)
			sus = 0;
		return sus;
	}
	else
	{
		sus = sus + 5;
		return sus;
	}

}

void emergencyMeeting()
{
	std::vector<int> crewSusCount(crewmateCount);
	
}