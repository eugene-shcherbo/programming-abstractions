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
    int bf;
    BSTNode* left;
    BSTNode* right;
};

void insertNode(BSTNode*& root, int key);
bool insertAVL(BSTNode*& root, int key);
bool insertLeft(BSTNode*& root, int key);
bool insertRight(BSTNode*& root, int key);

void removeNode(BSTNode*& root, int key);
bool removeAVL(BSTNode*& root, int key);
bool removeLeft(BSTNode*& root, int key);
bool removeRight(BSTNode*& root, int key);
bool removeNode(BSTNode*& node);
BSTNode* findLeftMostNode(BSTNode* root);

void fixLeftImbalance(BSTNode*& root);
void fixRightImbalance(BSTNode*& root);
void rotateRight(BSTNode*& root);
void rotateLeft(BSTNode*& root);

void displayTree(BSTNode* root, const string& space = "");
void free(BSTNode* node);

int main() {
    BSTNode* tree = nullptr;
    insertNode(tree, 43);
    insertNode(tree, 18);
    insertNode(tree, 22);
    insertNode(tree, 9);
    insertNode(tree, 21);
    insertNode(tree, 6);
    insertNode(tree, 8);
    insertNode(tree, 20);
    insertNode(tree, 63);
    insertNode(tree, 50);
    insertNode(tree, 62);
    insertNode(tree, 51);

    removeNode(tree, 62);
    removeNode(tree, 63);
    removeNode(tree, 51);
    removeNode(tree, 43);

    displayTree(tree);

    return 0;
}

void insertNode(BSTNode*& root, int key) {
    insertAVL(root, key);
}

bool insertAVL(BSTNode*& root, int key) {
    if (root == nullptr) {
        root = new BSTNode { key, 0, nullptr, nullptr };
        return true;
    } else if (root->key > key) {
        return insertLeft(root, key);
    } else if (root->key < key) {
        return insertRight(root, key);
    }
    return false;
}

bool insertLeft(BSTNode*& root, int key) {
    if (!insertAVL(root->left, key)) {
        return false;
    }
    switch (root->bf) {
    case -1:
        fixLeftImbalance(root);
        return false;
    case 0:
        root->bf = -1;
        return true;
    case 1:
        root->bf = 0;
        return false;
    }
    return false;
}

bool insertRight(BSTNode*& root, int key) {
    if (!insertAVL(root->right, key)) {
        return false;
    }
    switch (root->bf) {
    case -1:
        root->bf = 0;
        return false;
    case 0:
        root->bf = 1;
        return true;
    case 1:
        fixRightImbalance(root);
        return false;
    }
    return false;
}

void removeNode(BSTNode*& root, int key) {
    removeAVL(root, key);
}

bool removeAVL(BSTNode*& root, int key) {
    if (root == nullptr) {
        return false;
    } else if (root->key > key) {
        return removeLeft(root, key);
    } else if (root->key < key) {
        return removeRight(root, key);
    } else {
        return removeNode(root);
    }
}

bool removeLeft(BSTNode*& root, int key) {
    if (!removeAVL(root->left, key)) {
        return false;
    }
    switch (root->bf) {
    case -1:
        root->bf = 0;
        return true;
    case 0:
        root->bf = 1;
        return false;
    case 1:
        fixRightImbalance(root);
        return true;
    }
    return false;
}

bool removeRight(BSTNode*& root, int key) {
    if (!removeAVL(root->right, key)) {
        return false;
    }
    switch (root->bf) {
    case -1:
        fixLeftImbalance(root);
        return true;
    case 0:
        root->bf = -1;
        return false;
    case 1:
        root->bf = 0;
        return true;
    }
    return false;
}

bool removeNode(BSTNode*& node) {
    if (node->left == nullptr) {
        BSTNode* tmp = node->right;
        free(node);
        node = tmp;
        return true;
    } else if (node->right == nullptr) {
        BSTNode* tmp = node->left;
        free(node);
        node = tmp;
        return true;
    } else {
        BSTNode* leftMostNode = findLeftMostNode(node->right);
        int key = leftMostNode->key;
        bool isHeightChanged = removeAVL(node, leftMostNode->key);
        node->key = key;
        return isHeightChanged;
    }
}

BSTNode* findLeftMostNode(BSTNode* root) {
    if (root == nullptr) {
        return nullptr;
    } else if (root->left == nullptr) {
        return root;
    } else {
        return findLeftMostNode(root->left);
    }
}

void fixLeftImbalance(BSTNode*& root) {
    BSTNode* child = root->left;
    if (child->bf != root->bf) {
        int oldBf = child->right->bf;
        rotateLeft(root->left);
        rotateRight(root);
        switch (oldBf) {
            case -1:
                root->left->bf = 0;
                root->right->bf = 1;
                break;
            case 0:
                root->right->bf = 0;
                root->left->bf = 0;
                break;
            case 1:
                root->right->bf = 0;
                root->right->bf = -1;
        }
    } else {
        rotateRight(root);
        root->bf = 0;
        root->right->bf = 0;
    }
}

void fixRightImbalance(BSTNode*& root) {
    BSTNode* child = root->right;
    if (child->bf != root->bf) {
        int oldBf = child->left->bf;
        rotateRight(root->right);
        rotateLeft(root);
        switch (oldBf) {
            case -1:
                root->left->bf = 0;
                root->right->bf = 1;
                break;
            case 0:
                root->left->bf = 0;
                root->right->bf = 0;
                break;
            case 1:
                root->right->bf = 0;
                root->left->bf = -1;
                break;
        }

    } else {
        rotateLeft(root);
        root->bf = 0;
        root->left->bf = 0;
    }
}

void rotateRight(BSTNode*& root) {
    BSTNode* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root = tmp;
}

void rotateLeft(BSTNode*& root) {
    BSTNode* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root = tmp;
}

void displayTree(BSTNode* root, const string& space) {
    if (root != nullptr) {
        displayTree(root->right, space + "    ");
        cout << space << root->key << endl;
        displayTree(root->left, space + "    ");
    }
}

void free(BSTNode* node) {
    if (node != nullptr) {
        delete node;
    }
}

