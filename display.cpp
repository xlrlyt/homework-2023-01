//A: LLT
//Description: Display part

#include "display.hpp"

int getWindowHeight(){
    struct winsize wSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);
    return wSize.ws_row;
}
int getWindowWidth(){
    struct winsize wSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);
    return wSize.ws_col;
}
winsize getWindowSize(){
    struct winsize wSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);
    return wSize;
}
bool checkWindow(bool debug){
    struct winsize wSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wSize);
    if (debug){
        printf("row(Lines): %d, col(Width): %d\n", wSize.ws_row, wSize.ws_col);
    }
    if (wSize.ws_row < DISP_MIN_LINE || wSize.ws_col < DISP_MIN_WIDTH){
        return false;
    }
    return true;
}
int askOptions(OptionsList* options){

    printf("\033c");
    //build text
    restart:
    printf("%s:\n", options->title);
    int c = 0;
    while (c < options->optionsCount){
        printf("%d. %s\n", c + 1, options->optionsText[c]);
        c++;
    }
    char input = scanKey();
    input = input - '0';
    if (input < 1 || input > options->optionsCount){
        printf("\033c");
        printf("Please input a valid number!!\n");
        goto restart;
    }else{
        return input;
    }
    return 0;
}


char scanKey(){
    char input;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
      
    input = getchar();
      
    tcsetattr(0,TCSANOW,&stored_settings);
    return input;
}

void initGameInterface(int height, int width){
    
}