#include "binary_tree.h"

int compareTree(Arv A1, Arv A2) {
    if (A1 == NULL && A2 == NULL) return 1; 
    if (A1 == NULL || A2 == NULL) return 0; 

    if (A1->item == A2->item) { 
        return compareTree(A1->left, A2->left) && compareTree(A1->right, A2->right);
    } else {
        return 0;
    }
}

int main() {
    int arr1[] = {10, 5, 15, 2, 7, 12, 20};
    Arv tree1 = createTreeFromArray(arr1, sizeof(arr1) / sizeof(arr1[0]));

    int arr2[] = {10, 5, 15, 2, 7, 12, 20};
    Arv tree2 = createTreeFromArray(arr2, sizeof(arr2) / sizeof(arr2[0]));

    puts("Árvore 1:");
    printTreeVisual(tree1);
    puts("\nÁrvore 2:");
    printTreeVisual(tree2);

    printf("\nAs árvores %s\n", (compareTree(tree1, tree2) ? "são iguais!" : "não são iguais!"));

    return 0;
}
