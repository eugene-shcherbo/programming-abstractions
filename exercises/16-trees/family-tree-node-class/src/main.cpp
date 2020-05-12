#include <iostream>
#include <string>
#include "filelib.h"
#include "console.h"
#include "familytreenode.h"

using namespace std;

int main() {
    string filename = promptUserForFile("File name:");
    FamilyTreeNode* familyTree = readFamilyTree(filename);
    displayFamilyTree(familyTree);

    cout << endl;

    FamilyTreeNode* william1 = new FamilyTreeNode("William I");
    FamilyTreeNode* henry1 = new FamilyTreeNode("Henry I");
    FamilyTreeNode* william = new FamilyTreeNode("William");
    FamilyTreeNode* matilda = new FamilyTreeNode("Matilda");
    FamilyTreeNode* henry2 = new FamilyTreeNode("Henry II");
    FamilyTreeNode* henry3 = new FamilyTreeNode("Henry III");

    henry2->addChild(henry3);
    william->addChild(henry2);
    henry1->addChild(matilda);
    henry1->addChild(william);
    william1->addChild(henry1);

    cout << commonAncestor(henry3, matilda)->getName() << endl;

    return 0;
}
