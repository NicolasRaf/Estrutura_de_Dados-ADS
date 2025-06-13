#include <stdio.h>
#include "binary_tree.h"

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    Arv tree = createTreeFromArray(arr, sizeof(arr) / sizeof(arr[0]));

    printf("Árvore visual:\n");
    printTreeVisual(tree);
    printf("\n");

    destroy(&tree);

    return 0;
}
