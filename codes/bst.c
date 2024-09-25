#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Aðaç düðümleri için yapý tanýmý
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Yeni düðüm oluþturma fonksiyonu
struct Node* newNode(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Verilen aðacýn BST olup olmadýðýný kontrol eden fonksiyon
int isBSTUtil(struct Node* node, int min, int max) {
    // Boþ aðaç da BST kabul edilir
    if (node == NULL)
        return 1;

    // Geçerli düðüm deðeri sýnýrlar dýþýnda ise doðrudan 0 döner
    if (node->data < min || node->data > max)
        return 0;

    // Sol ve sað alt aðaçlarý da kontrol eder
    return isBSTUtil(node->left, min, node->data - 1) &&
           isBSTUtil(node->right, node->data + 1, max);
}

// BST kontrolünün baþlatýldýðý fonksiyon
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
        printf("Verilen aðaç bir BST'dir.\n");
    else
        printf("Verilen aðaç bir BST deðildir.\n");

    return 0;
}

