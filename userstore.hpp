#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEFAULT_USER_LIST_FILE "lltgame_userlist.conf"

struct UsersList {
    int userCount;
    const char **userIdList;
};

char* hash32bitL(const char* x);
UsersList getUserList(const char* listFileName = DEFAULT_USER_LIST_FILE);
void addToUserList(const char* userIdHash, const char* listFileName = DEFAULT_USER_LIST_FILE);
char* xtrim(char *str);