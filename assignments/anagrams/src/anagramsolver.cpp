// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <string>
#include "letterinventory.h"
#include "set.h"

using namespace std;

int anagramsHelper(LetterInventory& inventory, Vector<string>& anagrams, const Set<string>& dictionary, int max, int count);

void pruneDictionary(LetterInventory& inventory, const Set<string> dictionary, Set<string>& prunedDictionary) {
    for (string word: dictionary) {
        if (inventory.contains(word)) {
            prunedDictionary.add(word);
        }
    }
}

int findAnagrams(const string& phrase, int max, const Set<string>& dictionary) {
    Vector<string> anagrams;
    LetterInventory inventory(phrase);

    return anagramsHelper(inventory, anagrams, dictionary, max, 0);
}

int anagramsHelper(LetterInventory& inventory, Vector<string>& anagrams, const Set<string>& dictionary, int max, int count) {
    int totalFound = 0;

    if (inventory.isEmpty()) {
        cout << anagrams << endl;
        totalFound++;
    } else if (max == 0 || count < max) {
        Set<string> prunedDictionary;
        pruneDictionary(inventory, dictionary, prunedDictionary);

        for (string word: prunedDictionary) {
            anagrams.add(word);
            inventory.subtract(word);

            totalFound += anagramsHelper(inventory, anagrams, prunedDictionary, max, count + 1);

            anagrams.remove(anagrams.size() - 1);
            inventory.add(word);
        }
    }

    return totalFound;
}
