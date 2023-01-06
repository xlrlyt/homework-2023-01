

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_CONFIG_FILE "lltgame.conf"

#define DEFAULT_GAME_SPEED 1.0
#define DEFAULT_GAME_WIDTH 10
#define DEFAULT_GAME_HEIGHT 20

struct SettingStore
{
    float gameSpeed = DEFAULT_GAME_SPEED;
    int gameWidth = DEFAULT_GAME_WIDTH;
    int gameHeight = DEFAULT_GAME_HEIGHT;
    bool init = false;
};



void initSettingStore(const char* configFileName = DEFAULT_CONFIG_FILE);
void saveConfig(const char* configFileName = DEFAULT_CONFIG_FILE);
float getSpeed(); int getWidth(); int getHeight();
void modifySpeed(float);
void modifyHeight(int);
void modifyWidth(int);
void resetConfig();