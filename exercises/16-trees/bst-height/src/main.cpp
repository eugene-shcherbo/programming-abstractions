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
int height(BSTNode* root);

int main() {
    BSTNode* root = nullptr;
    insertNode(root, 18);
    insertNode(root, 22);
    insertNode(root, 8);
    insertNode(root, 6);
    insertNode(root, 9);
    insertNode(root, 21);
    insertNode(root, 50);
    insertNode(root, 20);
    insertNode(root, 63);
    insertNode(root, 43);
    insertNode(root, 62);


    cout << height(root) << endl;
    assert(height(root) == 4);

    return 0;
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

int height(BSTNode* root) {
    if (root == nullptr) {
        return -1;
    } else {
        int left = height(root->left);
        int right = height(root->right);

        return  1 + (left > right ? left : right);
    }
}
