#include "binary_tree.h"
#include "string.h"

Arv math_expression_node(char *expression){
    //((5+3)/4)* (6-1))
    //1 - analizar o primeiro colchete
    int lenght_expression = strlen(expression);
    for(int i = 0; i <= lenght_expression; i++){
        if(expression[i] == "("){
            
            //ignorar o restante de qualquer colchete
        }
    }
    //2 - as operações dentro dele serão a raiz da árvore
    //3 - os números dentro dela serão as próximos nós
    //4 - repetir o passo 01 para os itens a esquerda e a direita de novos parênteses 
}

int main(){
    Arv n4 = node(NULL, 4, NULL);
    Arv n5 = node(NULL, 5, NULL);
    Arv n6 = node(NULL, 6, NULL);
    Arv n7 = node(NULL, 7, NULL);
    Arv n3 = node(n7, 3, n6);
    Arv n2 = node(n4, 2, n5);
    Arv n1 = node(n2, 1, n3);

    printTreeVisual(n1);
    int binary_tree = strictly_binary_tree(n1);
    printf("A árvore %s", binary_tree == 1? "é estritamente binária" : "não é estritamente binária");
    printf("\n"); 

    return 0;
}