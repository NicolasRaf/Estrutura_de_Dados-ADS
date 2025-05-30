#include "binary_tree.h"

Arv node(Arv lef, int x, Arv rig){
    Arv n = (Arv)malloc(sizeof(struct arv));
    n->left = lef;
    n->item = x;
    n->right = rig;
    return n;
}

Arv createTreeFromArrayIndex(int arr[], int size, int i) {
    if (i >= size)
        return NULL;
    
    Arv left = createTreeFromArrayIndex(arr, size, 2 * i + 1);
    Arv right = createTreeFromArrayIndex(arr, size, 2 * i + 2);
    return node(left, arr[i], right);
}

Arv createTreeFromArray(int arr[], int size) {
    return createTreeFromArrayIndex(arr, size, 0);
}

void printLevel(Arv root, int level, int currLevel, int indent) {
    if (root == NULL) {
        if (currLevel == level) {
            for (int i = 0; i < indent; i++) printf(" ");
            printf("   ");  // espaço reservado para NULL
        } else {
            printLevel(NULL, level, currLevel + 1, indent / 2);
            printLevel(NULL, level, currLevel + 1, indent / 2);
        }
        return;
    }

    if (currLevel == level) {
        for (int i = 0; i < indent; i++) printf(" ");
        printf("%2d ", root->item);
    } else {
        printLevel(root->left, level    , currLevel + 1, indent / 2);
        printLevel(root->right, level, currLevel + 1, indent / 2);
    }
}

int height(Arv A) {
    if (A == NULL) return 0;
    int l = height(A->left);
    int r = height(A->right);
    return (l > r ? l : r) + 1;
}

void printTreeVisual(Arv root) {
    int h = height(root);
    int maxIndent = (1 << h) * SPACING;  // 2^h * espaçamento base

    for (int level = 0; level < h; level++) {
        if (level == 0) {
            printLevel(root, level, 0, maxIndent >> (level + 2));
            printf("\n");
            continue;
        }
        printLevel(root, level, 0, maxIndent >> (level + 1));
        printf("\n");
    }
}

void preOrder(Arv A) {
    if (A == NULL) return;
    printf("%d ", A->item);
    preOrder(A->left);
    preOrder(A->right);
}

void postOrder(Arv A) {
    if (A == NULL) return;
    postOrder(A->left);
    postOrder(A->right);
    printf("%d ", A->item);
}

void destroy(Arv *A) {
    if (*A == NULL) return;
    destroy(&(*A)->left);
    destroy(&(*A)->right);
    free(*A);
    *A = NULL;
}

void ins(int x, Arv *A) {
    if (*A == NULL)
        *A = node(NULL, x, NULL);
    else if (x <= (*A)->item)
        ins(x, &(*A)->left);
    else
        ins(x, &(*A)->right);
}

int search(int x, Arv A) {
    if (A == NULL) return 0;
    if (x == A->item) return 1;
    if (x <= A->item) return search(x, A->left);
    else return search(x, A->right);
}

int renMax(Arv *A) {
    if (*A == NULL) abort();
    while ((*A)->right != NULL)
        A = &(*A)->right;
    Arv n = *A;
    int x = n->item;
    *A = n->left;
    free(n);
    return x;
}

void rem(int x, Arv *A) {
    if (*A == NULL) return;
    if (x == (*A)->item) {
        Arv n = *A;
        if (n->left == NULL)
            *A = n->right;
        else if (n->right == NULL)
            *A = n->left;
        else
            n->item = renMax(&n->left);
        if (n != *A)
            free(n);
    } else if (x <= (*A)->item)
        rem(x, &(*A)->left);
    else
        rem(x, &(*A)->right);
}