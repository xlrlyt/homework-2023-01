//Description: The data part of the game
#include "kernel.hpp"

char** baseMap;
int currentBlockType;
int currentBlockHeight;
int currentBlockWidth;

int height, width;

void initKernel(){
    baseMap = (char**)malloc(sizeof(void*) * GAMEKERNEL_MAX_HEIGHT);
    for (int c = 0; c < GAMEKERNEL_MAX_HEIGHT; c++){
        baseMap[c] = (char*)malloc(GAMEKERNEL_MAX_WIDTH);
    }
}
bool initGame(int _height, int _width){
    if (_height < 10 || _height > GAMEKERNEL_MAX_HEIGHT || _width < 10 || _width > GAMEKERNEL_MAX_WIDTH) {
        printf("%s", "游戏设置无效\n");
        return false;
    }
    //clearmap
    for(int c = 0; c < _height; c++){
        for (int cc = 0; cc < _width; cc++){
            baseMap[c][cc] = 0;
        }
    }
    currentBlockType = -1;
    width = _width;
    height = _height;
    srand((int)time(0));
    return true;
}
void generateBlock(){
    currentBlockType = rand() / BLOCK_NUM;
    currentBlockHeight = 0;
    currentBlockWidth = rand() / (width - 4);
}

void testPrint(){
    initKernel();
    initAndCheckInterface(20, 20);
    initGame(20, 20);
    printRawMap(baseMap, 20, 20);
    sleep(1);
    printRawMap(baseMap, 20, 20);
}

void startGame(int _height, int _width){
    bool status = initGame(_height, _width);
    if (!status){
        printf("%s", "初始化游戏失败\n");
        sleep(2);
        return;
    }
    status = initAndCheckInterface(height, width);
    if (!status){
        printf("%s", "界面检测不通过\n");
        sleep(2);
        return;
    }
    printRawMap(baseMap, height, width);
    sleep(2);
}