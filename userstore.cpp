#include "userstore.hpp"


UserConfig userConfig;
char configFileName[100];


char* xtrim(char *str) {
	int first = -1;
	int last = -1;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' '
			&& str[i] != '\t'
			&& str[i] != '\n'
			&& str[i] != '\r') {
			first = i;
			break;
		}
	}
	if (first == -1) {
		str[0] = '\0';
		return str;
	}
	for (int i = first; str[i] != '\0'; i++) {
		if (str[i] != ' '
			&& str[i] != '\t'
			&& str[i] != '\n'
			&& str[i] != '\r') {
			last = i;
		}
	}
	str[last + 1] = '\0';
	return str + first;
}


char* hash32bitL(const char* x){
    srand(166);//generate a certain list
    char* result0 = new char[32];
    int c = 0;
    while (c < 32){
        result0[c] = x[c] ^ (rand() % 256);
        c++;
    }
    c = 0;
    char* result1 = new char[65];
    while (c < 32){
        sprintf(result1 + c * 2, "%02x", (unsigned char)(result0[c]));
        c++;
    }
    delete []result0;
    return result1;
}

UsersList getUserList(const char* listFileName){
    FILE* fp = fopen(listFileName, "r");
    UsersList userlist;
    if (fp == NULL){
        userlist.userCount = 0;
        return userlist;
    }else{
        char line[70];
        int lineLen;
        userlist.userIdList = (const char **)malloc(sizeof(void*) * 1);
        while (fgets(line, 70, fp)){
            lineLen = strlen(line);
            if (lineLen > 10){
                char* lineTrimed = xtrim(line);
                //this is not a empty line and it is a record
                char* tmp = new char[70];
                memcpy(tmp, line, 70);
                userlist.userIdList[userlist.userCount] = tmp;
                userlist.userCount++;
                userlist.userIdList = (const char **)realloc(userlist.userIdList, sizeof(void*) * (userlist.userCount + 1));
            }
        }
        fclose(fp);
        return userlist;
    }
}

void addToUserList(const char* userIdHash, const char* listFileName){
    FILE* fp = fopen(listFileName, "r");
    if (fp == NULL){
        fp = fopen(listFileName, "a");
        if (fp == NULL){
            printf("%s", "修改本地用户列表失败");
            return;
        }else{
            fprintf(fp, "%s\n", userIdHash);
            //fputs(userIdHash, fp);
            fclose(fp);
            return;
        }
    }else{
        char line[70];
        while (fgets(line, 70, fp)){
            char* lineTrimed = xtrim(line);
            //printf("DEBUG: USERLIST ADD COMPARE %s %s", lineTrimed, userIdHash);
            if (strcmp(lineTrimed, userIdHash) == 0){
                fclose(fp);
                return;
            }
        }
        fclose(fp);
        fp = fopen(listFileName, "a");
        fprintf(fp, "%s\n", userIdHash);
        fclose(fp);
    }
}


/*
userid: char*
username: char*
userphone: char*
score: int
playtime: int

*/
void initUserConfig(const char* userId){
    strcpy(configFileName, hash32bitL(userId));
    strcpy(configFileName + strlen(configFileName), "_userdata.conf");
    FILE* fp = fopen(configFileName, "r");
    if (fp == NULL){
        strcpy(userConfig.userid, userId);
        memset(userConfig.userPhone, 0, 20);
        strcpy(userConfig.userName, "DEFAULT");
    }else{
        char line[33];
        char* lineTrimed;
        //read userid
        fgets(line, 33, fp);
        lineTrimed = xtrim(line);
        strcpy(userConfig.userid, lineTrimed);
        //read name
        fgets(line, 33, fp);
        lineTrimed = xtrim(line);
        strcpy(userConfig.userName, lineTrimed);
        //read phone
        fgets(line, 33, fp);
        lineTrimed = xtrim(line);
        strcpy(userConfig.userPhone, lineTrimed);
        //read score
        fgets(line, 33, fp);
        userConfig.userScore = atoi(line);
        //read time
        fgets(line, 33, fp);
        userConfig.playTimeInSecond = atoi(line);
        fclose(fp);
    }
}
void saveUserConfig(){
    FILE* fp = fopen(configFileName, "w");
    if (fp == NULL){
        printf("%s", "保存用户基本数据错误");
        return;
    }else{
        //printf("%s\n%s\n%d\n%d", userConfig.userid, userConfig.userPhone, userConfig.userScore, userConfig.playTimeInSecond);

        fprintf(fp, "%s\n%s\n%s\n%d\n%d", userConfig.userid, userConfig.userName, userConfig.userPhone, userConfig.userScore, userConfig.playTimeInSecond);
        fclose(fp);
    }
}


const char* getUserId(){ return userConfig.userid; }
const char* getUserName(){ return userConfig.userName; }
const char* getUserPhone(){ return userConfig.userPhone; }
int getUserScore(){ return userConfig.userScore; }
int getUserTime(){ return userConfig.playTimeInSecond; }
void setUserName(const char* name){
    strcpy(userConfig.userName, name);
    saveUserConfig();
}
void setUserPhone(const char* phone){
    strcpy(userConfig.userPhone, phone);
    saveUserConfig();
}
void setUserScoreInternal(int score){
    userConfig.userScore = score;
    saveUserConfig();
}
void setUserTimeInternal(int time){
    userConfig.playTimeInSecond = time;
    saveUserConfig();
}