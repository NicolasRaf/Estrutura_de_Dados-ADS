#include "binary_tree.h"

int leafs(Arv A) {
    if (A == NULL) return 0; 

    if (A->left == NULL && A->right == NULL) 
        return 1; 

    return leafs(A->left) + leafs(A->right); 
}


int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printTreeVisual(tree);
    printf("Número de Folhas: %d", leafs(n1));
}