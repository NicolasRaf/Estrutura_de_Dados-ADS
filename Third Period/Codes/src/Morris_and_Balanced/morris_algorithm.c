#include "stdio.h"
#include "stdlib.h"

// Estrutura do nó (a mesma que você já tem)
struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
};

// --- Funções de Criação e Lógica da Árvore ---
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

struct No* inserir(struct No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->dado)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}


void visitar(struct No* no){
    printf("%d ", no->dado);
}
 
void morrisInOrder(struct No* raiz) {
    if (raiz == NULL) return;

    // Referência ao nó atual e variavel temporária para manipulação
    struct No* atual = raiz, *temp;

    // Enquanto o nó atual for diferente de NULL
    while(atual != NULL){

        // Se o nó atual nao tiver filho esquerdo
        if (atual->esquerda==NULL){
            visitar(atual); 
            atual = atual->direita; // Ir para o filho direito
        } else {
            temp = atual->esquerda;

            // Enquanto o filho direito nao for nulo e nao for o atual
            while (temp->direita != NULL && temp->direita != atual){
                temp = temp->direita;
            }

            if (temp->direita == NULL){
                temp->direita = atual;
                atual = atual->esquerda;
            } else {
                visitar(atual);
                temp->direita = NULL;
                atual = atual->direita;
            }
        }
    }
    puts("");
}

void morrisPreOrder(struct No* raiz) {
    // Referência ao nó atual e variavel temporária para manipulação
    struct No* atual = raiz, *temp;

      // Enquanto o nó atual for diferente de NULL
    while(atual != NULL){

        // Se o nó atual nao tiver filho esquerdo
        if (atual->esquerda==NULL){
            visitar(atual); 
            atual = atual->direita; // Ir para o filho direito
        } else {
            temp = atual->esquerda;

            // Enquanto o filho direito nao for nulo e nao for o atual
            while (temp->direita != NULL && temp->direita != atual){
                temp = temp->direita;
            }

            if (temp->direita == NULL){
                visitar(atual);
                temp->direita = atual;
                atual = atual->esquerda;
            } else {
                temp->direita = NULL;
                atual = atual->direita;
            }
        }
    }
    puts("");
}

int calcularAltura(struct No* no) {
    if (no == NULL) return 0;
    int altura_esq = calcularAltura(no->esquerda);
    int altura_dir = calcularAltura(no->direita);
    return (altura_esq > altura_dir) ? (altura_esq + 1) : (altura_dir + 1);
}

int cmpfunc(const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

// Função auxiliar para imprimir uma quantidade de espaços
void imprimir_espacos(int n) {
    for (int i = 0; i < n; i++) {
        printf(" ");
    }
}

// Função principal para imprimir a árvore de forma visual
void visualizarArvore(struct No* raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }

    int altura = calcularAltura(raiz);
    // Usa um array como fila para a travessia por nível
    // O tamanho precisa ser suficiente para o último nível

    int nos_max_nivel = 1 << altura; 
    struct No** fila = malloc(sizeof(struct No*) * nos_max_nivel);

    if (!fila) return;

    int nos_no_nivel_atual = 1;
    int indice_fila = 0;
    fila[0] = raiz;

    for (int i = 1; i <= altura; i++) {
        // Calcula o espaçamento para o nível atual
        // Espaço antes do primeiro nó
        int espaco_inicial = (1 << (altura - i)) - 1; 
        // Espaço entre os nós
        int espaco_entre = (1 << (altura - i + 1)) - 1;

        imprimir_espacos(espaco_inicial * 2); // Multiplicador para ajustar visualmente

        int proximos_nos = 0;
        struct No** proximo_nivel_fila = malloc(sizeof(struct No*) * nos_max_nivel);

        for (int j = 0; j < nos_no_nivel_atual; j++) {
            struct No* no = fila[j];
            if (no) {
                printf("%2d", no->dado); // Imprime o nó, usando 2 dígitos
                proximo_nivel_fila[proximos_nos++] = no->esquerda;
                proximo_nivel_fila[proximos_nos++] = no->direita;
            } else {
                printf("  "); // Espaço para um nó nulo
                proximo_nivel_fila[proximos_nos++] = NULL;
                proximo_nivel_fila[proximos_nos++] = NULL;
            }
            imprimir_espacos(espaco_entre * 2); // Multiplicador para ajustar
        }
        printf("\n\n"); // Espaçamento vertical entre níveis

        // Prepara para o próximo nível
        nos_no_nivel_atual = proximos_nos;
        free(fila); // Libera a fila do nível antigo
        fila = proximo_nivel_fila; // A fila do próximo nível se torna a fila atual
    }

    free(fila); // Libera a memória da última fila
}

int main(){

    struct No* raiz = NULL;
    struct No* aux = NULL;

    int numeros[] = {7, 6, 22, 14, 40, 63};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    // Inserção sequencial
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, numeros[i]);
        aux = inserir(aux, numeros[i]);
    }

    printf("\nVisualizacao da arvore:\n");
    printf("========================================\n");
    visualizarArvore(raiz);
    printf("========================================\n\n");


    printf("\nIn-ordem: \n"); 
    morrisInOrder(raiz); 

    printf("\nPre-ordem: \n "); 
    morrisPreOrder(aux);

    return 0;
}