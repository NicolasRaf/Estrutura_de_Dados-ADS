#include <iostream>
#include <queue>

using namespace std;
queue<char> aux;

void empilhar( queue<char> *pilha, char item ) {
    while (!(*pilha).empty()){
        aux.push((*pilha).front());
        (*pilha).pop();
    }
    (*pilha).push(item);

    while ( !aux.empty() ){
        (*pilha).push(aux.front());
        aux.pop();
    }
} 

char desempilhar( queue<char> *pilha ) {
    char resultado = (*pilha).front();
    (*pilha).pop();

    return resultado;
}

int main() {
    queue<char> pilha;

    empilhar(&pilha, 'u');
    empilhar(&pilha, 'a');
    empilhar(&pilha, 'p');

    while ( ! pilha.empty() ){
        printf("%c", desempilhar(&pilha) );
    }

    return 0;
}