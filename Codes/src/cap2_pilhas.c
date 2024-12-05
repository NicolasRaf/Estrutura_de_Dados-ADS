#include <stdio.h>
#include <stdlib.h>
#include "../utils/console_clear.h"
#include "../utils/pilha.h"

int main() {
    consoleClear();
    Pilha numerosP = inicializarPilha(10);
    numerosP->item = "a";

    printf("A pilha esta vazia? %d", pilhaVazia(numerosP));

    return 0;
}