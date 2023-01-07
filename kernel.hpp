//A: LLT
//Description: Header of the data part of the game
#pragma once

#include <stdlib.h>
#include "display.hpp"
#include "blockdata.hpp"
#include <time.h>
#include <pthread.h>

#define GAMEKERNEL_MAX_HEIGHT 100
#define GAMEKERNEL_MAX_WIDTH 100

void testPrint();
void startGame(int _height, int _width);
bool initGame(int _height, int _width);
void initKernel();
void refresh();
void execute(int operation);

/* content of cpp, rewrite with c
class GameKernel {
    public:
        GameKernel();
        GameKernel(int height, int width);
        int getWidth();
        int getHeight();
        bool execute(int operation); //return false if game failed
        int getMark(); //return the mark if game end, else return -1
        bool getEnd(); //return true if end
    private:
        char **_baseMap;
        int _height = 20;
        int _width = 10;
        int currentBlockType;
        int currentBlockH, currentBlockW;
        int currentBlockForward;
        void initData();
        
};*/