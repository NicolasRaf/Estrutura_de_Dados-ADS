#include <stdio.h>
#include "../utils/pilha.h"
#include "../utils/console_clear.h"


int main() {
    consoleClear();

    // Inicializando a pilha com capacidade para 5 elementos
    Pilha pilhaDeChar = inicializarPilha(5);

    // Empilhando alguns itens
    empilhar(pilhaDeChar, 'A');
    empilhar(pilhaDeChar, 'B');
    empilhar(pilhaDeChar, 'C');

    // Verificando se a pilha está vazia
    if (pilhaVazia(pilhaDeChar)) {
        printf("A pilha está vazia.\n");
    } else {
        printf("A pilha não está vazia.\n");
    }

    // Acessando o topo da pilha
    printf("Topo da pilha: %c\n", acessarPilha(pilhaDeChar));

    // Desempilhando o topo da pilha
    printf("Desempilhando: %c\n", desempilhar(pilhaDeChar));

    // Verificando novamente o topo após desempilhar
    printf("Novo topo da pilha: %c\n", acessarPilha(pilhaDeChar));

    // Destruindo a pilha para liberar memória
    destruirPilha(&pilhaDeChar);

    return 0;
}
