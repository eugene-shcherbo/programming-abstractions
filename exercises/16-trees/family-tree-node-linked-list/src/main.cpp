#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "vector.h"
#include "filelib.h"
#include "map.h"

using namespace std;

struct FamilyTreeNode {
    string name;
    FamilyTreeNode* sibling;
    FamilyTreeNode* child;
};

FamilyTreeNode* readFamilyTree(const string& filename);
void parseNames(const string& line, string& parent, string& child);
void displayFamilyTree(FamilyTreeNode* root, const string& indent="");
void insertChild(FamilyTreeNode* root, string parent, string child);
void insertChild(FamilyTreeNode* root, string child);

int main() {
    string filename = promptUserForFile("Enter a file name containing a family tree:");
    FamilyTreeNode* root = readFamilyTree(filename);
    displayFamilyTree(root);

    return 0;
}

FamilyTreeNode* readFamilyTree(const string& filename) {
    FamilyTreeNode* root = nullptr;
    ifstream infile(filename);
    string line;
    getline(infile, line);
    root = new FamilyTreeNode { line, nullptr, nullptr };
    while (getline(infile, line)) {
        string child;
        string parent;
        parseNames(line, parent, child);
        insertChild(root, parent, child);
    }

    return root;
}

void parseNames(const string& line, string& parent, string& child) {
    size_t separatorIndex = line.find(":");
    child = line.substr(0, separatorIndex);
    parent = line.substr(separatorIndex + 1);
}

void insertChild(FamilyTreeNode* root, string parent, string child) {
    if (root == nullptr) {
        return;
    } else if (root->name == parent) {
        insertChild(root, child);
    } else {
        insertChild(root->child, parent, child);
        insertChild(root->sibling, parent, child);
    }
}

void insertChild(FamilyTreeNode* root, string child) {
    if (root->child == nullptr) {
        root->child = new FamilyTreeNode { child, nullptr, nullptr };
    } else {
        FamilyTreeNode* curr = root->child;
        while (curr->sibling != nullptr) {
            curr = curr->sibling;
        }
        curr->sibling = new FamilyTreeNode { child, nullptr, nullptr };
    }
}

void displayFamilyTree(FamilyTreeNode* root, const string& indent) {
    if (root != nullptr) {
        cout << indent << root->name << endl;
        displayFamilyTree(root->child, indent + "  ");
        displayFamilyTree(root->sibling, indent);
    }
}
