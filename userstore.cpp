#include "userstore.hpp"

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