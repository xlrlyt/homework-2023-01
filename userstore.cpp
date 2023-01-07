#include "userstore.hpp"

char* xtrim(char *str) {
	int first = -1; //第一个空白字符的下标
	int last = -1; //最后一个空白字符的下标
	//找到第一个非空白字符
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' '
			&& str[i] != '\t'
			&& str[i] != '\n'
			&& str[i] != '\r') {
			first = i;
			break;
		}
	}
	if (first == -1) { //全是空白字符
		str[0] = '\0';
		return str;
	}
 
	//保存最后一个非空白字符的指针
	for (int i = first; str[i] != '\0'; i++) {
		if (str[i] != ' '
			&& str[i] != '\t'
			&& str[i] != '\n'
			&& str[i] != '\r') {
			last = i;
		}
	}
 
	//在最后一个非空白字符的后面赋值'\0'
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