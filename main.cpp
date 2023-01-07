//Author: LLT
//Description: Homework of GDUT
#include "blockdata.hpp"
#include "kernel.hpp"
#include "display.hpp"
#include "settingstore.hpp"
#include "userstore.hpp"
#include <string>
int main(){
    printf("%s", "请输入你的用户id: ");
    char* userid = new char[33];
    memset(userid, 0, 33);
    int ci = 0;
    char cc;
    while (ci < 32){
        cc = getchar();
        if (cc == '\n'){
            break;
        }
        userid[ci] = cc;
        ci++;
    }
    
    char* useridHash = hash32bitL(userid);
    addToUserList(useridHash);
    //printf("DEBUG: Userid Hash: %s\n", useridHash); return 0;
    //return 0;
    
    std::string configFileName = "";
    configFileName += useridHash;
    configFileName += "_settings.conf";
    bool windowOk = checkWindow(true);
    if (!windowOk){
        printf("The terminal size is too small, required: %d x %d\n", DISP_MIN_LINE, DISP_MIN_WIDTH);
        return -1;
    }
    initSettingStore(configFileName.c_str());
    saveConfig(configFileName.c_str());
    struct OptionsList options;
    options.optionsText = new const char*[5]{
        "开始游戏", "修改游戏设置", "修改你的信息", "查询历史信息", "退出"
    };
    options.optionsCount = 5;
    options.title = "选择你的操作";
    askOP:
    int userOp = askOptions(&options);
    
    if (userOp == 1){
        //start game
    }else if (userOp == 2)
    {
        //modify settings
        struct OptionsList modifyList;
        char* speedText = new char[40];
        char* heightText = new char[40];
        char* widthText = new char[40];
        
        modifyList.optionsText = new const char*[5]{
            speedText, heightText, widthText, "重置", "退出修改"
        };
        modifyList.title = "设置修改界面";
        modifyList.optionsCount = 5;
        OP2_SEL:
        sprintf(speedText, "速度乘区：%f", getSpeed());
        sprintf(heightText, "高度：%d", getHeight());
        sprintf(widthText, "宽度：%d", getWidth());
        int userOP2 = askOptions(&modifyList);
        if (userOP2 == 1){
            //modify speed
            printf("%s", "请输入新的速度乘区：");
            float _speed;
            scanf("%f", &_speed);
            modifySpeed(_speed);
            saveConfig(configFileName.c_str());
        }else if (userOP2 == 2){
            printf("%s", "请输入新的界面高度：");
            int _height;
            scanf("%d", &_height);
            modifyHeight(_height);
            saveConfig(configFileName.c_str());
        }else if (userOP2 == 3){
            printf("%s", "请输入新的界面宽度：");
            int _width;
            scanf("%d", &_width);
            modifyWidth(_width);
            saveConfig(configFileName.c_str());
        }else if (userOP2 == 4){
            resetConfig();
            saveConfig(configFileName.c_str());
        }else if (userOP2 == 5){
            goto OP2_SEL_END;
        }
        goto OP2_SEL;
        OP2_SEL_END:
        delete []speedText; delete []heightText; delete []widthText;

    }else if (userOp == 3){
        //modify user settings
    }else if (userOp == 4){
        //query user history
    }else if (userOp == 5){
        return 0;
    }
    goto askOP;
    return 0;
}