//Description: The data part of the game
#include "kernel.hpp"

char** baseMap;
int currentBlockType;
int currentBlockHeight;
int currentBlockWidth;
int currentBlockRotation;

pthread_t threadForBlock;
bool stopped = true;

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
    currentBlockType = rand() % BLOCK_NUM;
    currentBlockHeight = 0;
    currentBlockWidth = rand() % (width - 4);
    currentBlockRotation = rand() % 4;
}

void testPrint(){
    sleep(1);
    initKernel();
    initAndCheckInterface(20, 20);
    initGame(20, 20);
    printMixedMap(baseMap, 20, 20, 2, 2, 2, 2);
}

void* backgroundThread(void* arg){
    while (!stopped){
        execute(1);
        usleep(1 * 1000 * 1000);
    }
    refresh();
    printf("%s", "\n游戏结束，任意按键结束\n");
    return NULL;
}

void launchBackgroudThread(){
    pthread_create(&threadForBlock, NULL, backgroundThread, NULL);
}

bool blockStatusCheck(){
    const char (*block)[4] = getBlocks(currentBlockType, currentBlockRotation);
    bool end = false;
    for (int c = 0; c < 4; c++){
        for (int cc = 0; cc < 4; cc++){
            if (block[c][cc]){
                if (currentBlockHeight + c + 1 >= height){
                    end = true;
                    goto FINISH_BS_CHECK;
                }
                if (baseMap[currentBlockHeight + c + 1][currentBlockWidth + cc]){
                    end = true;
                    goto FINISH_BS_CHECK;
                }
            }
        }
    }
    FINISH_BS_CHECK:
    return end;
}
bool blockConflictCheck(){
    const char (*block)[4] = getBlocks(currentBlockType, currentBlockRotation);
    bool end = false;
    for (int c = 0; c < 4; c++){
        for (int cc = 0; cc < 4; cc++){
            if (block[c][cc]){
                if (currentBlockHeight + c >= height || currentBlockWidth + cc >= width || currentBlockHeight < 0 || currentBlockWidth < 0){
                    end = true;
                    goto FINISH_BS_CHECK;
                }
                if (baseMap[currentBlockHeight + c][currentBlockWidth + cc]){
                    end = true;
                    goto FINISH_BS_CHECK;
                }
            }
        }
    }
    FINISH_BS_CHECK:
    return end;
}
void mixMap(){
    const char (*block)[4] = getBlocks(currentBlockType, currentBlockRotation);
    
    for (int c = 0; c < 4; c++){
        for (int cc = 0; cc < 4; cc++){
            if (block[c][cc]){
                baseMap[currentBlockHeight + c][currentBlockWidth + cc] = 1;
                if (currentBlockHeight + c < height && currentBlockWidth + cc < width){
                    
                }
            }
        }
    }
}
/*
1: down
2: left
3: right
4: rotate
*/
void execute(int operation){
    bool result2;
    //check 1
    if (currentBlockType == -1){
        generateBlock();
        result2 = blockConflictCheck();
        if (result2){
            //failed
            stopped = true;
        }
    }
    bool result1 = blockStatusCheck();
    if (result1){
        //need to generate new block
        //ignore this operation
        mixMap();
        generateBlock();
        result2 = blockConflictCheck();
        if (result2){
            //failed
            stopped = true;
        }
        refresh();
        return;
    }
    if (operation == 1){
        currentBlockHeight++;
        refresh();
        return;
    }
    if (operation == 2){
        currentBlockWidth--;
        if (blockConflictCheck()){
            currentBlockWidth++;
            return;
        }
        refresh();
        return;
    }
    if (operation == 3){
        currentBlockWidth++;
        if (blockConflictCheck()){
            currentBlockWidth--;
            return;
        }
        refresh();
        return;
    }
    if (operation == 4){
        int orgrotation = currentBlockRotation;
        currentBlockRotation = (currentBlockRotation + 1) % 4;
        if (blockConflictCheck()){
            currentBlockRotation = orgrotation;
            return;
        }
        refresh();
    }
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
    //printRawMap(baseMap, height, width);
    stopped = false;
    refresh();
    launchBackgroudThread();
    char cxx;
    while (!stopped){
        cxx = scanKey();
        if (cxx == 'q' || cxx == 'Q'){
            stopped = true;
        }
        if (cxx == 'W' || cxx == 'w'){
            //ignore
        }
        if (cxx == 'a' || cxx == 'A'){
            execute(2);
        }
        if (cxx == 's' || cxx == 'S'){
            execute(1);
        }
        if (cxx == 'd' || cxx == 'D'){
            execute(3);
        }
        if (cxx == 'r' || cxx == 'R'){
            execute(4);
        }
        
    }
    pthread_join(threadForBlock, NULL);
    printf("游戏得分：%d, 3秒后退出\n", 0);
    sleep(3);
}
void refresh(){
    printMixedMap(baseMap, height, width, currentBlockType, currentBlockHeight, currentBlockWidth, currentBlockRotation);
}