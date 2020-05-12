#include <iostream>
#include <fstream>
#include "familytreenode.h"
#include "set.h"

FamilyTreeNode* readFamilyTree(std::ifstream& infile);
void addChild(FamilyTreeNode* root, const std::string parent, FamilyTreeNode* child);
void parseNames(const std::string& line, std::string& parent, std::string& child);
void displayFamilyTree(const FamilyTreeNode* root, const std::string& indent);

FamilyTreeNode::FamilyTreeNode(const std::string& name) {
    name_ = name;
    parent_ = nullptr;
}

std::string FamilyTreeNode::getName() const {
    return name_;
}

void FamilyTreeNode::addChild(FamilyTreeNode* child) {
    child->parent_ = this;
    children_.add(child);
}

FamilyTreeNode* FamilyTreeNode::getParent() const {
    return parent_;
}

Vector<FamilyTreeNode*> FamilyTreeNode::getChildren() const {
    return children_;
}

void displayFamilyTree(const FamilyTreeNode* root) {
    displayFamilyTree(root, "");
}

FamilyTreeNode* commonAncestor(FamilyTreeNode *p1, FamilyTreeNode *p2) {
    Set<FamilyTreeNode*> parents;

    for (FamilyTreeNode* parent = p1; parent != nullptr; parent = parent->getParent()) {
        parents.add(parent);
    }

    for (FamilyTreeNode* parent = p2; parent != nullptr; parent = parent->getParent()) {
        if (parents.contains(parent)) {
            return parent;
        }
    }

    return nullptr;
}

void displayFamilyTree(const FamilyTreeNode* root, const std::string& indent) {
    if (root != nullptr) {
        std::cout << indent << root->getName() << std::endl;
        for (FamilyTreeNode* child: root->getChildren()) {
            displayFamilyTree(child, indent + "  ");
        }
    }
}

FamilyTreeNode* readFamilyTree(const std::string& filename) {
    std::ifstream infile(filename);
    if (infile.good()) {
        return readFamilyTree(infile);
    } else {
        return nullptr;
    }
}

FamilyTreeNode* readFamilyTree(std::ifstream& infile) {
    std::string line;
    getline(infile, line);
    FamilyTreeNode* root = new FamilyTreeNode(line);

    while (getline(infile, line)) {
        std::string child;
        std::string parent;
        parseNames(line, parent, child);
        addChild(root, parent, new FamilyTreeNode(child));
    }

    return root;
}

void parseNames(const std::string& line, std::string& parent, std::string& child) {
    size_t separatorIndex = line.find(":");
    child = line.substr(0, separatorIndex);
    parent = line.substr(separatorIndex + 1);
}

void addChild(FamilyTreeNode* root, const std::string parent, FamilyTreeNode* child) {
    if (root == nullptr) {
        return;
    } else if (root->getName() == parent) {
        root->addChild(child);
    } else {
        for (FamilyTreeNode* c: root->getChildren()) {
            addChild(c, parent, child);
        }
    }
}
