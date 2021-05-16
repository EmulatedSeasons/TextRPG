#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <codecvt>
#include <Windows.h>

#include "UtilFunctions.h"
#include "StringReference.h"
#include "Map.h"

void howToScreen();
void fadeScreen();

void titleScreen()
{
	clearScreen();
	std::cout << StringRef::titleArt;
	std::cout << std::string(10, '\n');
	std::cout << R"(						(1) Play game
						(2) How to play guide
						(3) Quit
													)";

	while (true)
	{
		int option = getPlayerOption(1, 3);
		if (option == 1)
		{
			stopSound();
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			mapScreen();
			return;
		}
		else if (option == 2)
		{
			fadeScreen();
			howToScreen();
			break;
		}
		else if (option == 3)
		{
			exit(0);
			return;
		}
		option = 0;
		clearIOLine();
	}
}

//Fade out and in transition effect
void fadeScreen()
{
	setConsoleCursorPos(0, 0);
	std::cout << StringRef::transition1;
	Sleep(500);
	setConsoleCursorPos(0, 0);
	std::cout << std::string(120 * 27, '/');
	Sleep(500);
	clearScreen();
	Sleep(1000);
}

void howToScreen()
{
	std::cout << "Unfinished feature";
	Sleep(5000);
	fadeScreen();
}

