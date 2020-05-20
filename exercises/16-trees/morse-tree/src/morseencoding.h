#ifndef _morseencoding_h_
#define _morseencoding_h_

#include <string>

class MorseEncoding {
public:
    MorseEncoding();
    char getMorseCodeLetter(std::string code);
private:
    struct Node {
        char letter;
        Node* left;
        Node* right;
    };

    void insertLetter(Node*& root, const std::string& code, int codeIndex, char letter);
    char searchMorseTree(Node* root, const std::string& code, int codeIndex);

    Node* root;
};

#endif
