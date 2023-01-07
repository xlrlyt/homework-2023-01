//A: LLT
//Description: Header of display part
#pragma once
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>
#include "blockdata.hpp"

#define DISP_MIN_LINE 22
#define DISP_MIN_WIDTH 25
#define BLACK_CHAR "■"
#define EMPTY_CHAR "  " //design for windows ssh console
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

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
bool initAndCheckInterface(int height, int width);
void printRawMap(char **map, int height, int width);
void printMixedMap(char **map, int height, int width, int currentBlockType, int currentBlockHeight, int currentBlockWidth, int currentBlockRotation);