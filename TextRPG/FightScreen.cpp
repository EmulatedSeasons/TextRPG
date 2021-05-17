#include <iostream>
#include <cstdlib>
#include <string>
#include <codecvt>

#include <Windows.h>

#include "StringReference.h"
#include "Screen.h"
#include "UtilFunctions.h"
#include "FightScreen.h"

int specialAtkQantity = 3;

bool fightScreen(int& health, int& crewCount)
{
	//Used to print UTF-16 characters
	//Unicode doesn't seem to want to work properly but the text produces an image anyways
	std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> cv;

	//Enemy health
	int enemyHealth = 100;
	int enemyMaxHealth = 100;
	
	//Final boss checker
	if (crewCount == 1)
	{
		enemyHealth = 500;
		enemyMaxHealth = 500;
	}

	//Encounter chance
	if (crewCount != 1)
	{
		if (getRandomNumber(0, 100) > 50)
		{
			setConsoleCursorPos(0, 25);
			std::cout << "But nobody was here...";
			Sleep(5000);
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			return true;
		}
	}

	soundPlay("bgm/TRPGFightMusic.wav", true);

	while (true)
	{
		setConsoleCursorPos(0, 0);
		std::cout << cv.to_bytes(StringRef::crewmateArt);

		//Show player and enemy stats
		setConsoleCursorPos(0, 0);
		std::cout << "Your health: " << health << "/100";
		setConsoleCursorPos(0, 1);
		std::cout << "Enemy health: " << enemyHealth << '/' << enemyMaxHealth;
		setConsoleCursorPos(0, 2);
		std::cout << "Special attacks left: " << specialAtkQantity;

		setConsoleCursorPos(0, 25);
		std::cout << "(1)Attack\t(2)Special attack (" << specialAtkQantity << ")\t(3) Heal";
		int option = getPlayerOption(1, 3);
		if (option == 1)
		{
			int atkDmg = getRandomNumber(5, 15);
			int critChance = getRandomNumber(0, 100);
			if (critChance > 80)
			{
				atkDmg = atkDmg * 2;
				enemyHealth = enemyHealth - atkDmg;
			}
			else
			{
				enemyHealth = enemyHealth - atkDmg;
			}
		}
		else if (option == 2)
		{
			int atkDmg = getRandomNumber(50, 100);
			int critChance = getRandomNumber(0, 100);

			//Check if there are any special attacks left
			if (specialAtkQantity == 0)
			{
				int atkDmg = getRandomNumber(5, 15);
				if (critChance > 80)
				{
					atkDmg = atkDmg * 2;
					enemyHealth = enemyHealth - atkDmg;
				}
				else
				{
					enemyHealth = enemyHealth - atkDmg;
				}
			}
			else
			{
				if (critChance > 80)
				{
					atkDmg = atkDmg * 2;
					enemyHealth = enemyHealth - atkDmg;
				}
				else
				{
					enemyHealth = enemyHealth - atkDmg;
				}
			}
			--specialAtkQantity;
		}
		else if (option == 3)
		{
			health = health + getRandomNumber(15, 25);
			if (health > 100)
			{
				health = 100;
			}
		}

		//Enemy damage
		if (crewCount > 1)
		{
			health = health - getRandomNumber(5, 10);
		}
		else
		{
			health = health - getRandomNumber(10, 20);
		}

		//Check if you or the enemy have died
		if (health <= 0)
		{
			setConsoleCursorPos(0, 25);
			std::cout << "\033[2K";
			std::cout << "You lost";
			Sleep(5000);
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			return false;
		}
		if (enemyHealth <= 0)
		{
			--crewCount;
			setConsoleCursorPos(0, 25);
			std::cout << "\033[2K";
			std::cout << "You won";
			++specialAtkQantity;
			Sleep(5000);
			soundPlay("bgm/TRPGSnareNoise.wav", false);
			fadeScreen();
			return true;
		}
	}
}