#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <Windows.h>
#include <mmsystem.h>

//Lets std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); work
#undef max

void setConsoleCursorPos(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coords;
    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(hOut, coords);
}

//Clears the terminal screen and resets the cursor to (0, 0)
void clearScreen()
{
    for (int i = 0; i < 30; i++)
    {
        setConsoleCursorPos(0, i);
        std::cout << "\033[2K";
    }
    setConsoleCursorPos(0, 0);
}

//Clears the line where options are entered
void clearIOLine()
{
    //Clear lines 27 to 29
    for (int i = 27; i < 30; i++)
    {
        setConsoleCursorPos(0, i);
        std::cout << "\033[2K";
    }
    setConsoleCursorPos(0, 27);
    //Add a line of -------
    std::cout << std::string(120, '-');
    //Set cursor to line 28
    setConsoleCursorPos(0, 28);
}

//Enables ANSI escape codes for cmd.exe
void enableANSIEscapeCMD()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

//Error checking input function
int getPlayerOption(int min, int max)
{
    clearIOLine();
    setConsoleCursorPos(0, 26);
    std::cout << "\033[2K";
    setConsoleCursorPos(0, 28);

    int option = 1;
    std::cin.clear();
    while (true)
    {
        std::cin >> option;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            option = 0;
        }

        clearIOLine();
        if (option >= min && option <= max)
        {
            return option;
        }
        else if (option < min && option > max)
        {
            std::cout << '\a';
        }
    }
}

//Similar to getPlayerInput but without a min/max number. Useful for the task function
int getNumInput()
{
    clearIOLine();
    int answer;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> answer;
    return answer;
}

//Wondows Playsound but with less text to write each playsound call
void soundPlay(std::string filename, bool loop)
{
    if (loop)
    {
        PlaySoundA(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else
    {
        PlaySoundA(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
}

void stopSound()
{
    PlaySound(NULL, 0, 0);
}

int getRandomNumber(int min, int max)
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}