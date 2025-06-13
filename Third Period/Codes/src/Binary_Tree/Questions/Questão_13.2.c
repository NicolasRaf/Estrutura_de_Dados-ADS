#include "binary_tree.h"

int qtd_node_tree(Arv A){
    if (A == NULL) return 0;
    return 1 + qtd_node_tree(A->left) + qtd_node_tree(A->right);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printTreeVisual(tree);
    int quantidade_nos = qtd_node_tree(tree);
    printf("A quantidade total de nós é de: %d", quantidade_nos);
    printf("\n");

    return 0;
}