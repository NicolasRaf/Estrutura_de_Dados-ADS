#include "binary_tree.h"

int qtd_node_tree(Arv A){
    if (A == NULL) return 0;
    return 1 + qtd_node_tree(A->left) + qtd_node_tree(A->right);
}

int altura_arvore(Arv A){
    if(A == NULL) return 0;
    if(qtd_node_tree(A -> left) >= qtd_node_tree(A -> right)){
        return qtd_node_tree(A -> left);
    }else{
        return qtd_node_tree(A -> right);
    }
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printTreeVisual(tree);
    int altura_arv = altura_arvore(tree);
    printf("A altura da árvore é de: %d", altura_arv);
    printf("\n");

    return 0;
}