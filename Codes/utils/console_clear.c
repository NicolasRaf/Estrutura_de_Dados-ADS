#include <stdlib.h>

void consoleClear(){
    #if defined WIN32 || WIN64
        system("cls");
    #else
        system("clear");
    #endif 

}