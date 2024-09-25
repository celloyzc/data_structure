#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A�a� d���mleri i�in yap� tan�m�
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Yeni d���m olu�turma fonksiyonu
struct Node* newNode(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Verilen a�ac�n BST olup olmad���n� kontrol eden fonksiyon
int isBSTUtil(struct Node* node, int min, int max) {
    // Bo� a�a� da BST kabul edilir
    if (node == NULL)
        return 1;

    // Ge�erli d���m de�eri s�n�rlar d���nda ise do�rudan 0 d�ner
    if (node->data < min || node->data > max)
        return 0;

    // Sol ve sa� alt a�a�lar� da kontrol eder
    return isBSTUtil(node->left, min, node->data - 1) &&
           isBSTUtil(node->right, node->data + 1, max);
}

// BST kontrol�n�n ba�lat�ld��� fonksiyon
int isBST(struct Node* node) {
    return isBSTUtil(node, INT_MIN, INT_MAX);
}

// Ana fonksiyon
int main() {
    struct Node* root = newNode(4);
    root->left = newNode(2);
    root->left->left = newNode(1);
    root->left->right = newNode(3);
    root->right = newNode(5);

    if (isBST(root))
        printf("Verilen a�a� bir BST'dir.\n");
    else
        printf("Verilen a�a� bir BST de�ildir.\n");

    return 0;
}

