#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEFAULT_USER_LIST_FILE "lltgame_userlist.conf"

struct UsersList {
    int userCount;
    const char **userIdList;
};

struct UserConfig {
    char userid[33];
    char userName[33];
    char userPhone[20];
    int userScore = 0;
    int playTimeInSecond = 0;
};

char* hash32bitL(const char* x);
UsersList getUserList(const char* listFileName = DEFAULT_USER_LIST_FILE);
void addToUserList(const char* userIdHash, const char* listFileName = DEFAULT_USER_LIST_FILE);
char* xtrim(char *str);
void initUserConfig(const char* userId);
void saveUserConfig();
const char* getUserId();
const char* getUserName();
const char* getUserPhone();
int getUserScore();
int getUserTime();
void setUserName(const char* name);
void setUserPhone(const char* phone);
void setUserScoreInternal(int score);
void setUserTimeInternal(int time);