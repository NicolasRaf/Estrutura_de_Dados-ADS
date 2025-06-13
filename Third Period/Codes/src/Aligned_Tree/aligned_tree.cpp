#include <iostream>
using namespace std;

template<class T>
class ThreadedNode {
public:
    ThreadedNode() {
        left = right = 0;
    }

    ThreadedNode(const T& e1, ThreadedNode *l = 0, ThreadedNode *r = 0) {
        el = e1; left = l; right = r; successor = 0;
    }

    T el;
    ThreadedNode *left, *right;
    unsigned int successor : 1;
};

template<class T>
class ThreadedTree {
public:
    ThreadedTree() {
        root = 0;
    }

    void insert(const T&);
    void inorder();

        ThreadedNode<T>* getRoot() {
        return root;
    }

protected:
    ThreadedNode<T>* root;
};

template<class T>
void visit(ThreadedNode<T>* node) {
    cout << node->el << " ";
}

template<class T>
void ThreadedTree<T>::inorder() {
    ThreadedNode<T> *prev, *p = root;
    if (p != 0) {
        while (p->left != 0)
            p = p->left;
        while (p != 0) {
            visit(p);
            prev = p;
            p = p->right;
            if (p != 0 && prev->successor == 0)
                while (p->left != 0)
                    p = p->left;
        }
    }
}

template<class T>
void ThreadedTree<T>::insert(const T& el) {
    ThreadedNode<T> *p, *prev = 0, *newNode;
    newNode = new ThreadedNode<T>(el);
    if (root == 0) {
        root = newNode;
        return;
    }

    p = root;
    while (p != 0) {
        prev = p;
        if (p->el > el)
            p = p->left;
        else if (p->successor == 0)
            p = p->right;
        else break;
    }

    if (prev->el > el) {
        prev->left = newNode;
        newNode->successor = 1;
        newNode->right = prev;
    }
    else if (prev->successor == 1) {
        newNode->successor = 1;
        prev->successor = 0;
        newNode->right = prev->right;
        prev->right = newNode;
    }
    else prev->right = newNode;
}   

int main() {
    ThreadedTree<int> tree;

    // Inserindo elementos
    tree.insert(40);
    tree.insert(20);
    tree.insert(60);
    tree.insert(10);
    tree.insert(30);
    tree.insert(50);
    tree.insert(70);

    cout << "Percurso inorder (com threads): ";
    tree.inorder();
    cout << endl;

    return 0;
}
