#include <stdio.h>
#include <stdlib.h>

// Definindo o nó da árvore
typedef struct No {
    int valor;
    struct No *left, *right;
} No;

// Criação do nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

// Percurso In-Order usando Morris Traversal
void percursoInOrder(No *root) {
    No *p = root, *tmp; // 'p' é o nó atual, 'tmp' será usado para achar o predecessor

    while (p != NULL) { // Enquanto ainda há nós para percorrer
        if (p->left == NULL) { 
            // Caso não tenha filho à esquerda:
            // ✅ Visita o nó diretamente (não precisa voltar depois)
            printf("%d ", p->valor);
            // ➡️ Move para o filho da direita
            p = p->right;
        } else {
            // Caso tenha filho à esquerda, precisamos processar primeiro a subárvore esquerda
            tmp = p->left; // Guarda a subárvore esquerda

            // 🔍 Encontrando o predecessor: 
            // O predecessor é o nó mais à direita da subárvore esquerda
            while (tmp->right != NULL && tmp->right != p) // Se o filho da direita existir, e não apontar para 'p':
                tmp = tmp->right;

            if (tmp->right == NULL) {
                // Se o predecessor ainda não aponta para 'p':
                // ➕ Cria um link temporário de volta para 'p'
                tmp->right = p;
                // ➡️ Move para o filho da esquerda
                p = p->left;
            } else {
                // Se o link já existia (significa que voltamos da subárvore esquerda):
                // 🔄 Remove o link temporário
                tmp->right = NULL;
                // ✅ Visita o nó atual
                printf("%d ", p->valor);
                // ➡️ Move para a subárvore direita
                p = p->right;
            }
        }
    }
}


// Percurso Pré-Ordem usando Morris Traversal
void percursoPreOrdem(No *root) {
    No *p = root, *tmp; // 'p' é o nó atual, 'tmp' usado para achar o predecessor

    while (p != NULL) { // Enquanto houver nós para visitar
        if (p->left == NULL) {
            // ✅ Se não tem filho à esquerda:
            // Visita diretamente
            printf("%d ", p->valor);
            // ➡️ Move para a direita
            p = p->right;
        } else {
            // 🔍 Encontrando o predecessor (nó mais à direita da subárvore esquerda)
            tmp = p->left;
            while (tmp->right != NULL && tmp->right != p)
                tmp = tmp->right;

            if (tmp->right == NULL) {
                // Se o predecessor ainda não aponta para 'p':
                // ✅ Visita o nó AGORA (diferente do In-Order, onde só visita depois da esquerda)
                printf("%d ", p->valor);
                // ➕ Cria o link temporário para voltar depois
                tmp->right = p;
                // ➡️ Move para a esquerda
                p = p->left;
            } else {
                // Se o link temporário já estava criado:
                // 🔄 Remove o link
                tmp->right = NULL;
                // ➡️ Move para a direita
                p = p->right;
            }
        }
    }
}


// Função principal de teste
int main() {
    // Montando a árvore
    No *root = criarNo(60);
    root->left = criarNo(40);
    root->right = criarNo(80);
    root->left->left = criarNo(20);
    root->left->right = criarNo(50);
    root->left->left->right = criarNo(25);

    printf("Percurso In-Order: ");
    percursoInOrder(root);
    printf("\n");

    printf("Percurso Pre-Ordem: ");
    percursoPreOrdem(root);
    printf("\n");

    return 0;
}