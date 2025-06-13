#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

#define fmt "%d"
#define MAX_HEIGHT 10  // profundidade máxima da árvore
#define SPACING 4      // espaço horizontal entre os nós


// Definição da estrutura da árvore binária
typedef struct arv {
    struct arv *left;
    int item;
    struct arv *right;
} *Arv;

// Função para liberar memória da árvore
void destroy(Arv *A);

// Função para inserir um elemento na árvore
void ins(int x, Arv *A);

// Função para buscar um elemento na árvore
int search(int x, Arv A);

// Função para remover o maior elemento da árvore e retornar seu valor
int renMax(Arv *A);

// Função para remover um elemento específico da árvore
void rem(int x, Arv *A);

void printLevel(Arv root, int level, int currLevel, int indent);

int height(Arv A);

// Função para criar um novo nó da árvore
Arv node(Arv lef, int x, Arv rig);

Arv createTreeFromArray(int arr[], int size);

// Funções de percurso
void preOrder(Arv A);
void postOrder(Arv A);
void printTreeVisual(Arv A);

#endif // ARV_H