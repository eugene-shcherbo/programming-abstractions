#include "morseencoding.h"


MorseEncoding::MorseEncoding() {
    root = new Node { '\0', nullptr, nullptr };

    insertLetter(root, ".", 0, 'E');
    insertLetter(root, "-", 0, 'T');

    insertLetter(root, "..", 0, 'I');
    insertLetter(root, ".-", 0, 'A');
    insertLetter(root, "-.", 0, 'N');
    insertLetter(root, "--", 0, 'M');

    insertLetter(root, "...", 0, 'S');
    insertLetter(root, "..-", 0, 'U');
    insertLetter(root, ".-.", 0, 'R');
    insertLetter(root, ".--", 0, 'W');
    insertLetter(root, "-..", 0, 'D');
    insertLetter(root, "-.-", 0, 'K');
    insertLetter(root, "--.", 0, 'G');
    insertLetter(root, "---", 0, 'O');

    insertLetter(root, "....", 0, 'H');
    insertLetter(root, "...-", 0, 'V');
    insertLetter(root, "..-.", 0, 'F');
    insertLetter(root, ".-..", 0, 'L');
    insertLetter(root, ".--.", 0, 'P');
    insertLetter(root, ".---", 0, 'J');
    insertLetter(root, "-...", 0, 'B');
    insertLetter(root, "-..-", 0, 'X');
    insertLetter(root, "-.-.", 0, 'C');
    insertLetter(root, "-.--", 0, 'Y');
    insertLetter(root, "--..", 0, 'Z');
    insertLetter(root, "--.-", 0, 'Q');
}

void MorseEncoding::insertLetter(Node*& root, const std::string& code, int codeIndex, char letter) {
    if (codeIndex == code.size()) {
        root = new Node { letter, nullptr, nullptr };
    } else {
        char morseSymbol = code[codeIndex];

        if (morseSymbol == '.') {
            insertLetter(root->left, code, codeIndex + 1, letter);
        } else if (morseSymbol == '-') {
            insertLetter(root->right, code, codeIndex + 1, letter);
        }
    }
}

char MorseEncoding::getMorseCodeLetter(std::string code) {
    return searchMorseTree(root, code, 0);
}

char MorseEncoding::searchMorseTree(Node* root, const std::string& code, int codeIndex) {
    if (codeIndex == code.size()) {
        return root->letter;
    } else if (code[codeIndex] == '.') {
        return searchMorseTree(root->left, code, codeIndex + 1);
    } else if (code[codeIndex] == '-') {
        return searchMorseTree(root->right, code, codeIndex + 1);
    } else {
        throw "unknown morse symbol";
    }
}
