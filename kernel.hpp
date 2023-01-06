//A: LLT
//Description: Header of the data part of the game
#pragma once
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
        
};