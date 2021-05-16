/*
Code only works on windows due to using windows specific headers
*/

#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

#include "StringReference.h"
#include "UtilFunctions.h"
#include "Screen.h"

int main()
{
    //Enables ANSI escape sequences
    enableANSIEscapeCMD();
    //Makes cin read newlines
    std::cin.unsetf(std::ios::skipws);
    //Set random generator seed
    std::srand((unsigned int)std::time(nullptr));
    
    //Begining story diolouge and music start
    soundPlay("bgm/TRPGIntro.wav", false);

    std::cout << "\n\n\n\n\n\n\tLine 1";
    Sleep(4300);
    std::cout << "\n\n\n\n\tLine 2";
    Sleep(4300);
    std::cout << "\n\n\n\n\tLine 3";
    Sleep(4300);
    std::cout << "\n\n\n\n\tLine 4";

    Sleep(7100);
    soundPlay("bgm/TRPGSnareNoise.wav", false);
    fadeScreen();
    Sleep(2000);

    //Game loop
    bool gameIsRunning = 1;
    while (true)
    {
        soundPlay("bgm/TRPGTitleScreen.wav", true);
        titleScreen();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
