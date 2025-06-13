#include <stdio.h>
#include <stdlib.h>

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

int calcularAltura(struct No* no) {
    if (no == NULL) return 0;
    int altura_esq = calcularAltura(no->esquerda);
    int altura_dir = calcularAltura(no->direita);
    return (altura_esq > altura_dir) ? (altura_esq + 1) : (altura_dir + 1);
}

struct No* construirArvoreBalanceada(struct No* raiz, int vetor[], int inicio, int fim) {
    if (inicio > fim) {
        return NULL; // Retornar NULL é mais limpo aqui
    }
    int meio = inicio + (fim - inicio) / 2; // Evita overflow para arrays muito grandes
    
    // O elemento do meio se torna a raiz
    raiz = criarNo(vetor[meio]);

    // Constrói recursivamente as subárvores
    raiz->esquerda = construirArvoreBalanceada(raiz->esquerda, vetor, inicio, meio - 1);
    raiz->direita = construirArvoreBalanceada(raiz->direita, vetor, meio + 1, fim);

    return raiz;
}

int cmpfunc(const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}


/* ----------------- FUNÇÕES DE IMPRESSÃO VISUAL ----------------- */

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


// ------------------------- FUNÇÃO PRINCIPAL ATUALIZADA -------------------------
int main() {
    // ---- Árvore 1: Inserção Sequencial (Desbalanceada) ----
    struct No* raiz_desbalanceada = NULL;
    int numeros[] = {7, 6, 22, 14, 40, 63};
    int n = sizeof(numeros) / sizeof(numeros[0]);
    
    printf("--- Arvore 1: Criada por Insercao Sequencial ---\n");
    printf("Inserindo na ordem: 7, 6, 22, 14, 40, 63\n\n");

    // Inserção sequencial
    for (int i = 0; i < n; i++) {
        raiz_desbalanceada = inserir(raiz_desbalanceada, numeros[i]);
    }

    printf("Visualizacao da arvore desbalanceada:\n");
    printf("========================================\n");
    visualizarArvore(raiz_desbalanceada); // CHAMADA DA NOVA FUNÇÃO
    printf("========================================\n\n");


    // ---- Árvore 2: Construção Balanceada ----
    struct No* raiz_balanceada = NULL; 
    
    printf("--- Arvore 2: Criada por Algoritmo de Balanceamento ---\n");

    // Ordena o vetor para a construção
    qsort(numeros, n, sizeof(int), cmpfunc);
    printf("Vetor ordenado para a construcao: ");
    for(int i = 0; i < n; i++) printf("%d ", numeros[i]);
    printf("\n\n");
    
    // Construção da Árvore Balanceada
    raiz_balanceada = construirArvoreBalanceada(NULL, numeros, 0, n - 1);

    printf("Visualizacao da arvore balanceada:\n");
    printf("========================================\n");
    visualizarArvore(raiz_balanceada); // CHAMADA DA NOVA FUNÇÃO
    printf("========================================\n");
    
    free(raiz_desbalanceada);
    free(raiz_balanceada);
    
    return 0;
}   