

#include "settingstore.hpp"


/*
speed: float
height: int
width: int
*/
SettingStore _iSettingStore;

void initSettingStore(const char* configFileName){
    //try to read file
    FILE* fp = fopen(configFileName, "r");
    if (fp == NULL){
        //create default config
        _iSettingStore.init = true;

    }else{
        int res = fscanf(fp, "%f %d %d", &(_iSettingStore.gameSpeed), &(_iSettingStore.gameHeight), &(_iSettingStore.gameWidth));//ignore the result
        fclose(fp);
        
    }
}
void saveConfig(const char* configFileName){
    FILE* fp = fopen(configFileName, "w");
    char buff[255];
    sprintf(buff, "%f %d %d", _iSettingStore.gameSpeed, _iSettingStore.gameHeight, _iSettingStore.gameWidth);
    fputs(buff, fp);
    fclose(fp);
}
float getSpeed(){
    return _iSettingStore.gameSpeed;
}
int getWidth(){
    return _iSettingStore.gameWidth;
}
int getHeight(){
    return _iSettingStore.gameHeight;
}
void modifySpeed(float speed){
    _iSettingStore.gameSpeed = speed;
}
void modifyHeight(int height){
    _iSettingStore.gameHeight = height;
}
void modifyWidth(int width){
    _iSettingStore.gameWidth = width;
}
void resetConfig(){
    _iSettingStore.gameHeight = DEFAULT_GAME_HEIGHT;
    _iSettingStore.gameSpeed = DEFAULT_GAME_SPEED;
    _iSettingStore.gameWidth = DEFAULT_GAME_WIDTH;
}