#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

#define avancar(i, f) (i = (i + 1) % f->tamMax)

typedef char Itemf;

typedef struct fila {
    int tamMax;
    int total;
    int inicio;
    int final;
    Itemf *items;
} *Fila;

// Inicializa a fila com tamanho máximo
Fila inicializarFila(int tam) {
    Fila f = (Fila) malloc(sizeof(struct fila));
    if (!f) {
        puts("Erro ao alocar memória para a fila!");
        exit(EXIT_FAILURE);
    }

    f->tamMax = tam;
    f->inicio = 0;
    f->final = 0;
    f->total = 0;
    f->items = (char *) malloc(tam * sizeof(Itemf));
    if (!f->items) {
        free(f);
        puts("Erro ao alocar memória para os itens!");
        exit(EXIT_FAILURE);
    }

    return f;
}

// Verifica se a fila está vazia
int filaVazia(Fila f) {
    return (f->total == 0);
}

// Verifica se a fila está cheia
int filaCheia(Fila f) {
    return (f->total == f->tamMax);
}

// Adiciona um item à fila
void enfileirar(Fila f, Itemf item) {
    if (filaCheia(f)) {
        puts("Erro: Tentativa de enfileirar em uma fila cheia.");
        exit(EXIT_FAILURE);
    }

    f->items[f->final] = item;
    avancar(f->final, f);
    f->total++;
}

// Remove um item da fila
Itemf desenfileirar(Fila f) {
    if (filaVazia(f)) {
        puts("Erro: Tentativa de desenfileirar em uma fila vazia.");
        exit(EXIT_FAILURE);
    }

    Itemf item = f->items[f->inicio];
    avancar(f->inicio, f);
    f->total--;

    return item;
}

// Libera a memória da fila
void destruirFila(Fila *f) {
    free((*f)->items);
    free(*f);
    *f = NULL;
}

Itemf acessaUltimoFila(Fila f) {   
    return f->items[f->final-1];
}

#endif
