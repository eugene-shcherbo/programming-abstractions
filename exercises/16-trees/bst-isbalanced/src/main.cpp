#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "filelib.h"
#include "map.h"

using namespace std;

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
};

void insertNode(BSTNode*& root, int key);
bool isBalanced(BSTNode* root);
BSTNode* imbalancedTree();
BSTNode* balancedTree();

int main() {
    BSTNode* imbalanced = imbalancedTree();
    BSTNode* balanced = balancedTree();

    assert(!isBalanced(imbalanced));
    assert(isBalanced(balanced));

    return 0;
}

BSTNode* imbalancedTree() {
    BSTNode* root = nullptr;
    insertNode(root, 28);
    insertNode(root, 25);
    insertNode(root, 23);
    insertNode(root, 21);
    insertNode(root, 30);
    insertNode(root, 32);
    return root;
}

BSTNode* balancedTree() {
    BSTNode* root = nullptr;
    insertNode(root, 28);
    insertNode(root, 25);
    insertNode(root, 26);
    insertNode(root, 23);
    insertNode(root, 21);
    insertNode(root, 30);
    insertNode(root, 32);
    return root;
}

void insertNode(BSTNode*& root, int key) {
    if (root == nullptr) {
        root = new BSTNode { key, nullptr, nullptr };
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

int balanceHelper(BSTNode* root, bool& isBalanced) {
    if (root == nullptr) {
        isBalanced = true;
        return 0;
    } else {
        bool leftBalanced;
        bool rightBalanced;

        int leftHeight = balanceHelper(root->left, leftBalanced);
        int rightHeight = balanceHelper(root->right, rightBalanced);

        isBalanced = abs(rightHeight - leftHeight) < 2 && leftBalanced && rightBalanced;

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

bool isBalanced(BSTNode* root) {
    bool balance;
    balanceHelper(root, balance);
    return balance;
}
