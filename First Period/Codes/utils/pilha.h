#ifndef PILHA_H  // Se ainda não foi definido o identificador PILHA_H
#define PILHA_H  // Define o identificador PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef char ItenmP;

typedef struct pilha {
    int tamMax;       // Tamanho máximo da pilha
    int topo;         // Índice do topo da pilha
    ItenmP *item;     // Vetor para armazenar os itens da pilha
} *Pilha;

// Inicializa a pilha com o tamanho máximo especificado
Pilha inicializarPilha(int max) {
    Pilha tempP = (Pilha) malloc(sizeof(struct pilha));
    if (!tempP) {
        puts("Erro ao alocar memória para a pilha!");
        exit(EXIT_FAILURE);
    }

    tempP->tamMax = max;
    tempP->topo = -1;
    tempP->item = (char *) malloc(max * sizeof(ItenmP));
    if (!tempP->item) {
        puts("Erro ao alocar memória para os itens da pilha!");
        free(tempP);
        exit(EXIT_FAILURE);
    }

    return tempP;
}

// Retorna 1 se a pilha estiver vazia, 0 caso contrário
int pilhaVazia(Pilha p) {
    return (p->topo == -1);
}

// Retorna 1 se a pilha estiver cheia, 0 caso contrário
int pilhaCheia(Pilha p) {
    return (p->topo == (p->tamMax - 1));
}

// Insere um item no topo da pilha
void empilhar(Pilha p, ItenmP item) {
    if (pilhaCheia(p)) {
        puts("Pilha Cheia!");
        abort();
    }

    p->item[++p->topo] = item;
}

// Remove e retorna o item no topo da pilha
ItenmP desempilhar(Pilha p) {
    if (pilhaVazia(p)) {
        puts("Pilha Vazia!");
        abort();
    }

    return p->item[p->topo--];
}

// Retorna o item no topo da pilha sem removê-lo
ItenmP acessarPilha(Pilha p) {
    if (pilhaVazia(p)) {
        puts("Pilha Vazia!");
        abort();
    }

    return p->item[p->topo];
}

// Libera a memória alocada para a pilha
void destruirPilha(Pilha *p) {
    free((*p)->item);
    free(*p);
    *p = NULL;
}

#endif // Fim do guard PILHA_H
