#include <stdio.h>
#include "../utils/console_clear.h"
#include "../utils/fila.h"

int main() {
    consoleClear(); // Limpa a tela para um início mais limpo
    printf("Inicializando fila com capacidade para 5 elementos...\n");
    
    // Inicializa a fila
    Fila filaDeChar = inicializarFila(5);

    // Testando o enfileiramento
    printf("Enfileirando elementos: 'A', 'B', 'C'...\n");
    enfileirar(filaDeChar, 'A');
    enfileirar(filaDeChar, 'B');
    enfileirar(filaDeChar, 'C');

    // Testando o desenfileiramento
    printf("Desenfileirando: %c\n", desenfileirar(filaDeChar));
    printf("Desenfileirando: %c\n", desenfileirar(filaDeChar));

    // Testa o estado da fila (vazia ou não)
    if (filaVazia(filaDeChar)) {
        printf("A fila está vazia.\n");
    } else {
        printf("A fila não está vazia.\n");
    }

    // Enfileira mais elementos
    printf("Enfileirando elementos: 'D', 'E', 'F'...\n");
    enfileirar(filaDeChar, 'D');
    enfileirar(filaDeChar, 'E');

    // Tentativa de enfileirar com fila cheia
    printf("Tentando enfileirar 'F' em uma fila com capacidade máxima...\n");
    enfileirar(filaDeChar, 'F'); // Isso deve causar erro de fila cheia

    // Desenfileira os itens restantes
    printf("Desenfileirando: %c\n", desenfileirar(filaDeChar));
    printf("Desenfileirando: %c\n", desenfileirar(filaDeChar));
    printf("Desenfileirando: %c\n", desenfileirar(filaDeChar));

    // Verifica novamente se a fila está vazia
    if (filaVazia(filaDeChar)) {
        printf("Agora a fila está vazia.\n");
    } else {
        printf("A fila ainda não está vazia.\n");
    }

    // Testa tentativa de desenfileirar com fila vazia
    printf("Tentando desenfileirar de uma fila vazia...\n");
    desenfileirar(filaDeChar); // Isso deve causar erro de fila vazia

    // Libera a memória alocada para a fila
    destruirFila(&filaDeChar);
    printf("Fila destruída com sucesso.\n");

    return 0;
}
