#ifndef _lexicon_h_
#define _lexicon_h_

#include <string>

namespace text {

    class Lexicon {
    public:
        Lexicon(const std::string& filename);
        ~Lexicon();

        void addWord(const std::string& word);
        bool contains(const std::string& word);
        bool containsPrefix(const std::string& prefix);
        void clear();

    private:
        struct TrieNode {
            bool isWord;
            TrieNode** children;
        };

        TrieNode* trie_;
        bool contains(const std::string& word, bool isPrefix);
        void clear(TrieNode* root);
    };

}

#endif
