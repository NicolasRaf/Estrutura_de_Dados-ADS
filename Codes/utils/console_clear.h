#ifndef CONSOLE_CLEAR_H
#define CONSOLE_CLEAR_H

#include <stdio.h>
#include <stdlib.h>

// Limpa a tela do console
void consoleClear() {
    #ifdef _WIN32 || _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

#endif // CONSOLE_CLEAR_H
