#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "vector.h"
#include "map.h"

using namespace std;

struct FamilyTreeNode {
    string name;
    Vector<FamilyTreeNode*> children;
};

FamilyTreeNode* readFamilyTree(const string& filename);
void fillFamilyTree(const Map<string, Vector<string>>& family, FamilyTreeNode* root);
void displayFamilyTree(FamilyTreeNode* root, const string& indent="");
void readFamilyMapFromFile(ifstream& infile, Map<string, Vector<string>>& family);

int main() {
    FamilyTreeNode* root = readFamilyTree("Normandy.txt");
    displayFamilyTree(root);

    return 0;
}

FamilyTreeNode* readFamilyTree(const string& filename) {
    FamilyTreeNode* root = nullptr;
    ifstream infile(filename);

    if (infile.good()) {
        Map<string, Vector<string>> family;
        string line;
        getline(infile, line);
        root = new FamilyTreeNode { line, Vector<FamilyTreeNode*>() };
        readFamilyMapFromFile(infile, family);
        fillFamilyTree(family, root);
    }

    return root;
}

void fillFamilyTree(const Map<string, Vector<string>>& family, FamilyTreeNode* root) {
    if (root != nullptr) {
        Vector<string> children = family[root->name];
        for (string child: children) {
            FamilyTreeNode* childTree = new FamilyTreeNode { child, Vector<FamilyTreeNode*>() };
            fillFamilyTree(family, childTree);
            root->children.add(childTree);
        }
    }
}

void readFamilyMapFromFile(ifstream& infile, Map<string, Vector<string>>& family) {
    string line;
    while (getline(infile, line)) {
        size_t separatorIndex = line.find(":");
        string child = line.substr(0, separatorIndex);
        string parent = line.substr(separatorIndex + 1);

        if (family.containsKey(parent)) {
            family[parent].add(child);
        } else {
            family.add(parent, Vector<string> { child });
        }
    }
}

void displayFamilyTree(FamilyTreeNode* root, const string& indent) {
    if (root != nullptr) {
        cout << indent << root->name << endl;
        for (FamilyTreeNode* child: root->children) {
            displayFamilyTree(child, indent + "  ");
        }
    }
}
