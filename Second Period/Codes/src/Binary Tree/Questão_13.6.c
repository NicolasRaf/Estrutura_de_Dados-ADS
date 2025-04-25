#include "binary_tree.h"

int strictly_binary_tree(Arv A){
    if (A == NULL) return 1;
    if ((A->left == NULL && A->right != NULL) || (A->left != NULL && A->right == NULL)) {
        return 0;
    }
    return strictly_binary_tree(A->left) && strictly_binary_tree(A->right);
}

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printTreeVisual(tree);
    int binary_tree = strictly_binary_tree(tree);
    printf("A árvore %s", binary_tree == 1? "é estritamente binária" : "não é estritamente binária");
    printf("\n"); 

    return 0;
}