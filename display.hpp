//A: LLT
//Description: Header of display part
#pragma once
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>

#define DISP_MIN_LINE 22
#define DISP_MIN_WIDTH 25
#define BLACK_CHAR '■'

winsize getWindowSize();
int getWindowWidth();
int getWindowHeight();
struct OptionsList
{
    const char* title;
    const char** optionsText;
    int optionsCount;
};
int askOptions(OptionsList* options);
bool checkWindow(bool debug = false);
char scanKey();
void initGameInterface(int height, int width);