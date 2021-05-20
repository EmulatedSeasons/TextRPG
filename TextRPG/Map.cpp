#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <Windows.h>

#include "UtilFunctions.h"
#include "Screen.h"
#include "StringReference.h"
#include "Map.h"
#include "FightScreen.h"

//Could be private class member variables. Not sure if I can use classes for this assignment
//Could also use a struct
int room = 5;
bool hasWon = false;
int turnCounter = 0;
int crewmateCount = 5;
int susMeter = 10;
int health = 100;
const int maxHealth = 100;

void mapScreen()
{
	//Reset all values to defaults
	room = 5;
	hasWon = false;
	turnCounter = 0;
	crewmateCount = 5;
	susMeter = 10;
	health = 100;

	soundPlay("bgm/TRPGMapScreen.wav", true);
	
	while (true)
	{
		//Check if all crewmates have been defeated
		if (crewmateCount == 0)
		{
			hasWon = true;
			break;
		}
		//Check if there's 1 crewmate left
		if (crewmateCount == 1)
		{
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			health = 100;
			hasWon = fightScreen(health, crewmateCount);
			break;
		}

		//Check if 5 turnes have passed to call an emergency meeting
		if (turnCounter == 5)
		{
			fadeScreen();
			bool hasPlayerBeenKicked = emergencyMeeting();
			turnCounter = 0;
			fadeScreen();
			if (hasPlayerBeenKicked)
			{
				hasWon = false;
				break;
			}
		}

		//Prints out the ASCII map
		std::cout << StringRef::mapEmpty;

		//Displays player stats on the right
		setConsoleCursorPos(65, 0);
		std::cout << "Sus: " << susMeter;
		setConsoleCursorPos(65, 1);
		std::cout << "Room: " << room;
		setConsoleCursorPos(65, 2);
		std::cout << "Health: " << health;;

		//Asks the user what they want to do
		setConsoleCursorPos(0, 25);
		std::cout << "Select options: (1)Move room (2)Do task (3)Fight (if other crewmates are in the same room) (4)Heal";
		int option = getPlayerOption(1, 4);
		if (option == 1)
		{
			room = roomSelector();
		}
		else if (option == 2)
		{
			susMeter = doTask(susMeter);
		}
		else if (option == 3)
		{
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			bool wonFight = fightScreen(health, crewmateCount);
			soundPlay("bgm/TRPGMapScreen.wav", true);
			if (!wonFight)
			{
				hasWon = false;
				break;
			}
		}
		else if (option == 4)
		{
			health = health + getRandomNumber(10, 15);
			if (health > 100)
			{
				health = 100;
			}
		}

		if (health == 0)
		{
			hasWon = false;
			break;
		}
		susMeter = susMeter + 10;
		++turnCounter;
	}
	
	//Check if the player won the game
	if (hasWon)
	{
		fadeScreen();
		std::cout << StringRef::youWonText;
		Sleep(5000);
		soundPlay("bgm/TRPGSnareNoise.wav", false);
		fadeScreen();
	}
	else if (!hasWon)
	{
		fadeScreen();
		std::cout << StringRef::gameOverText;
		Sleep(5000);
		soundPlay("bgm/TRPGSnareNoise.wav", false);
		fadeScreen();
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

bool emergencyMeeting()
{
	std::vector<int> crewSusCount(crewmateCount + 1);
	std::vector <int> sortedSus(crewmateCount + 1);
	for (int i = 0; i < crewmateCount; ++i)
	{
		int sus = getRandomNumber(30, 100);
		crewSusCount[i] = sus;
		sortedSus[i] = sus;
	}
	int playerSusLocation = crewSusCount.size() - 1;
	crewSusCount[playerSusLocation] = susMeter;
	sortedSus[playerSusLocation] = susMeter;

	//Sorting the crewmates from highest to lowest sus levels
	std::sort(sortedSus.begin(),sortedSus.end(), std::greater<int>{});

	//Find which sus amount belongs to which crewmate
	bool isPlayer = false;
	
	//Prints out the results of the emergency meeting
	setConsoleCursorPos(0, 0);
	for (int i = 0; i < crewmateCount; ++i)
	{
		std::cout << "Crewmate " << i << ". Sus: " << crewSusCount[i] << '\n';
	}
	std::cout << "You. Sus: " << crewSusCount[playerSusLocation];

	for (int i = 0; i < crewmateCount + 1; ++i)
	{
		if (sortedSus[0] == crewSusCount[i])
		{
			if (i == playerSusLocation)
			{
				setConsoleCursorPos(0, 25);
				std::cout << "You had the highest sus level. You were ejected.";
				isPlayer = true;
				Sleep(10000);
				return isPlayer;
			}
			else
			{
				setConsoleCursorPos(0, 25);
				std::cout << "Crewmate " << i << " had the highest sus level. Crewmate " << i << " has been ejected";
				--crewmateCount;
				isPlayer = false;
				Sleep(10000);
				return isPlayer;
			}
		}
	}

}
