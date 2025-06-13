#include "binary_tree.h"

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printTreeVisual(tree);
    int busca = search(7, tree);
    printf("A busca retornou %s", busca == 1? "o seu item" : "nenhum dos itens buscados");
    printf("\n");

    return 0;
}