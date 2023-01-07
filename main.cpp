//Author: LLT
//Description: Homework of GDUT
#include "blockdata.hpp"
#include "kernel.hpp"
#include "display.hpp"
#include "settingstore.hpp"
#include "userstore.hpp"
#include <string>
int main(){
    //testPrint(); return 0;
    //input basic data
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
    //init userdata and usersettings
    char* useridHash = hash32bitL(userid);
    addToUserList(useridHash);
    initUserConfig(userid);
    saveUserConfig();
    std::string configFileName = "";
    configFileName += useridHash;
    configFileName += "_settings.conf";
    bool windowOk = checkWindow(true);
    if (!windowOk){
        printf("The terminal size is too small, required: %d x %d\n", DISP_MIN_LINE, DISP_MIN_WIDTH);
        return -1;
    }
    initKernel();
    initSettingStore(configFileName.c_str());
    saveConfig(configFileName.c_str());
    //start menu part
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
        //printf("%s", "DEBUG: ???????????");
        //return 0;
        startGame();
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
        struct OptionsList modifyList;
        char* useridText = new char[60];
        char* usernameText = new char[60];
        char* userphoneText = new char[60];
        char* scoreText = new char[60];
        char* timeText = new char[60];
        
        modifyList.optionsText = new const char*[6]{
            useridText, usernameText, userphoneText, scoreText, timeText, "退出修改"
        };
        modifyList.title = "用户信息修改与查询界面";
        modifyList.optionsCount = 6;
        OP3_SEL:
        sprintf(useridText, "用户id（不可修改）：%s", getUserId());
        sprintf(usernameText, "用户名：%s", getUserName());
        sprintf(userphoneText, "手机号：%s", getUserPhone());
        sprintf(scoreText, "综合得分（不可修改）：%d", getUserScore());
        sprintf(timeText, "游戏时长秒数（不可修改）：%d", getUserTime());
        int userOP3 = askOptions(&modifyList);
        if (userOP3 == 2){
            //modify username
            printf("%s", "请输入新的用户名：");//32
            char input[33];
            ci = 0;
            while (ci < 32){
                cc = getchar();
                if (cc == '\n'){
                    break;
                }
                input[ci] = cc;
                ci++;
            }
            input[ci] = 0;
            setUserName(input);
        }else if (userOP3 == 3){
            //modify phone
            printf("%s", "请输入新的手机号：");
            char input[20];
            ci = 0;
            while (ci < 19){
                cc = getchar();
                if (cc == '\n'){
                    break;
                }
                input[ci] = cc;
                ci++;
            }
            input[ci] = 0;
            setUserPhone(input);
        }else if (userOP3 == 6){
            goto OP3_SEL_END;
        }
        goto OP3_SEL;
        OP3_SEL_END:
        delete []useridText; delete []usernameText; delete []userphoneText; delete []scoreText; delete []timeText;
    }else if (userOp == 4){
        //query user history
        
        int curPage = 0;
        int c4;
        RecordList* recordList = getUserRecords();
        const int recordPrePage = 10;
        char userOP4;
        OP4_REFRESH:
        //usleep(50*1000);
        CLEAR_SCREEN();
        MOVETO(0,0);
        usleep(500*1000);
        printf("历史记录查询：共计%d条，当前第%d页，每页%d条\n", recordList->recordCount, curPage + 1, recordPrePage);
        c4 = 0;
        char times[40];
        time_t tmt;
        while (c4 < recordPrePage && c4 + curPage * recordPrePage < recordList->recordCount){
            tmt = (time_t)recordList->recordList[c4].startTime;
            struct tm* TMTM = localtime(&tmt);
            strftime(times, 80, "%Y-%m-%d %H:%M:%S  %Z", TMTM);

            printf("%d. 开始时间：%s, 耗时：%d秒, 得分：%d\n", c4 + 1, 
            times
            , recordList->recordList[c4].costTime, recordList->recordList[c4].score);
            c4++;
        }
        printf("输入1或2进行翻页，3退出\n");
        
        userOP4 = scanKey();
        if (userOP4 == '1'){
            if (curPage > 0){
                curPage--;
            }
        }else if (userOP4 == '2')
        {
            if (curPage < recordList->recordCount / recordPrePage){
                curPage++;
            }
        }else if (userOP4 == '3'){
            goto OP4_END;
        }
        goto OP4_REFRESH;

        OP4_END:
        1 == 1;
    }else if (userOp == 5){
        return 0;
    }
    goto askOP;
    return 0;
}