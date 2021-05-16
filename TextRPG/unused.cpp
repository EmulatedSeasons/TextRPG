#include <iostream>
#include <Windows.h>

void mouseDance()
{
    while (true)
    {
        for (int y = 0; y < 1080; y = y + 10)
        {
            for (int x = 0; x < 1920; x = x + 10)
            {
                SetCursorPos(x, y);
            }
        }
    }
}

//Unused Sleep() replacement function
void waitTime(int time)
{
    std::time_t startTime = std::time(nullptr);
    while (true)
    {
        if (std::difftime(std::time(nullptr), startTime) >= time)
        {
            break;
        }
    }
}