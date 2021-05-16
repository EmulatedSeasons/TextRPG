#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <string>
#include <Windows.h>

void clearScreen();
void enableANSIEscapeCMD();
void clearIOLine();
void setConsoleCursorPos(int, int);
int getPlayerOption(int min, int max);
int getNumInput();
void soundPlay(std::string, bool);
void stopSound();
int getRandomNumber(int, int);

#endif
