#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// Estrutura de um nó da árvore de Huffman
struct Node {
    char caractere;
    int frequencia;
    Node *esquerda, *direita;
    int tomaz;

    Node(char c, int f) : caractere(c), frequencia(f), esquerda(nullptr), direita(nullptr) {}
};

// Comparador para o min-heap (priority_queue)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequencia > b->frequencia;
    }
};

// Função recursiva para gerar os códigos de Huffman
void gerarCodigos(Node* raiz, string codigo, unordered_map<char, string>& codigos) {
    if (!raiz) return;
    if (!raiz->esquerda && !raiz->direita) {
        codigos[raiz->caractere] = codigo;
    }
    gerarCodigos(raiz->esquerda, codigo + "0", codigos);
    gerarCodigos(raiz->direita, codigo + "1", codigos);
}

// Função principal para construir a árvore de Huffman e imprimir os códigos
/**
 * @brief Constrói a árvore de Huffman para um texto e imprime os códigos
 *        binários correspondentes.
 * @param texto O texto para ser codificado.
 */
void huffman(const string& texto) {
    // Contagem de frequência de cada caractere
    unordered_map<char, int> freq;

    // Contando a frequência de cada caractere
    for (char c : texto) {
        freq[c]++;
    }

    // Criando o min-heap (fila de prioridade)
    priority_queue<Node*, vector<Node*>, Compare> heap;

    // Adicionando os nós na fila de prioridade
    for (unordered_map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        char caractere = it->first;
        int f = it->second;
        heap.push(new Node(caractere, f));
    }

    // Construindo a árvore de Huffman
    while (heap.size() > 1) {
        Node* esq = heap.top(); heap.pop();
        Node* dir = heap.top(); heap.pop();

        Node* novo = new Node('\0', esq->frequencia + dir->frequencia);
        novo->esquerda = esq;
        novo->direita = dir;
        heap.push(novo);
    }

    // Gerando os códigos binários
    unordered_map<char, string> codigos;
    gerarCodigos(heap.top(), "", codigos);

    cout << "Códigos de Huffman:\n";
    for (unordered_map<char, string>::iterator it = codigos.begin(); it != codigos.end(); ++it) {
        char caractere = it->first;
        string codigo = it->second;
        cout << caractere << ": " << codigo << "\n";
    }

    // Exemplo de codificação de texto
    string codificado;
    for (char c : texto) {
        codificado += codigos[c];
    }

    cout << "\nTexto original: " << texto << "\n";
    cout << "Texto codificado: " << codificado << "\n";
}

int main() {
    string texto = "tung tung tung sarrur";
    huffman(texto);
    return 0;
}