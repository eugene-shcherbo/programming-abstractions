// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <string>
#include "letterinventory.h"
#include "set.h"

using namespace std;

void anagramsHelper(LetterInventory& inventory, Vector<string>& anagrams, const Set<string>& dictionary, int& count);

int findAnagrams(const string& phrase, int max, const Set<string>& dictionary) {
    Vector<string> anagrams;
    LetterInventory inventory(phrase);
    int count = 0;

    anagramsHelper(inventory, anagrams, dictionary, count);

    return count;
}

void anagramsHelper(LetterInventory& inventory, Vector<string>& anagrams, const Set<string>& dictionary, int& count) {
    if (inventory.isEmpty()) {
        cout << anagrams << endl;
        count++;
    } else {
        for (string word: dictionary) {
            if (inventory.contains(word)) {
                anagrams.add(word);
                inventory.subtract(word);

                anagramsHelper(inventory, anagrams, dictionary, count);

                anagrams.remove(anagrams.size() - 1);
                inventory.add(word);
            }
        }
    }
}
