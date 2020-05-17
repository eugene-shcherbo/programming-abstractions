#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "filelib.h"
#include "map.h"

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

void insertNode(Node*& root, int key);
Node* createBST();
Node* createNonBST();
bool isBST(Node* root);
bool isBST(Node* root, int min, int max);

int main() {
    Node* bst = createBST();
    Node* nonBst = createNonBST();

    assert(isBST(bst));
    assert(!isBST(nonBst));

    return 0;
}

void insertNode(Node*& root, int key) {
    if (root == nullptr) {
        root = new Node { key, nullptr, nullptr };
    } else {
        if (root->key != key) {
            if (root->key > key) {
                insertNode(root->left, key);
            } else {
                insertNode(root->right, key);
            }
        }
    }
}

Node* createBST() {
    Node* bst = nullptr;
    insertNode(bst, 18);
    insertNode(bst, 22);
    insertNode(bst, 8);
    insertNode(bst, 6);
    insertNode(bst, 9);
    insertNode(bst, 21);
    insertNode(bst, 50);
    insertNode(bst, 20);
    insertNode(bst, 63);
    insertNode(bst, 43);
    insertNode(bst, 62);

    return bst;
}

Node* createNonBST() {
    Node* tree = new Node { 2, nullptr, nullptr };
    tree->left = new Node { 9, nullptr, nullptr };
    tree->left->left = new Node { 0, nullptr, nullptr };
    tree->left->right = new Node { 8, nullptr, nullptr };
    tree->right = new Node { 1, nullptr, nullptr };
    tree->right->left = new Node { 50, nullptr, nullptr };
    tree->right->right = new Node { 32, nullptr, nullptr };

    return tree;
}

bool isBST(Node* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

bool isBST(Node* root, int min, int max) {
    if (root == nullptr) {
        return true;
    } else if (root->key < min || root->key > max) {
        return false;
    } else {
        return isBST(root->left, min, root->key - 1)
               && isBST(root->right, root->key + 1, max);
    }
}
