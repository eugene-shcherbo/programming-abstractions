#include <fstream>
#include "lexicon.h"
#include "strlib.h"

int letterNum(char ch);

namespace text {

    Lexicon::Lexicon(const std::string& filename) {
        trie_ = new TrieNode { false, new TrieNode*[26]() };
        std::ifstream infile(filename);

        if (infile.fail()) {
            throw "error: can't open a file named '" + filename  + "'";
        }

        std::string word;
        while (getline(infile, word)) {
            addWord(word);
        }
    }

    Lexicon::~Lexicon() {
        clear();
    }

    void Lexicon::addWord(const std::string& word) {
        TrieNode* node = trie_;

        for (char ch: word) {
            if (node->children[letterNum(toLowerCase(ch))] == nullptr) {
                node->children[letterNum(toLowerCase(ch))] = new TrieNode { false, new TrieNode*[26]() };
            }
            node = node->children[letterNum(toLowerCase(ch))];
        }

        node->isWord = true;
    }

    bool Lexicon::contains(const std::string& word) {
        return contains(word, /* isPrefix */ false);
    }

    bool Lexicon::containsPrefix(const std::string& prefix) {
        return contains(prefix, /* isPrefix */ true);
    }

    bool Lexicon::contains(const std::string& word, bool isPrefix) {
        TrieNode* node = trie_;

        for (char ch: word) {
            if (node->children[letterNum(toLowerCase(ch))] == nullptr) {
                return false;
            }
            node = node->children[letterNum(toLowerCase(ch))];
        }

        return isPrefix ? true : node->isWord;
    }

    void Lexicon::clear() {
        clear(trie_);
    }

    void Lexicon::clear(TrieNode* root) {
        if (root != nullptr) {
            for (int i = 0; i < 26; i++) {
                clear(root->children[i]);
            }
            delete root;
        }
    }

}

int letterNum(char ch) {
    return ch - 'a';
}
