#include "encoding.h"
#include "priorityqueue.h"
using namespace std;

Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable { {PSEUDO_EOF, 1} };

    while (true) {
        int ch = input.get();
        if (ch == EOF) {
            break;
        } else if (!freqTable.containsKey(ch)) {
            freqTable[ch] = 1;
        } else {
            freqTable[ch]++;
        }
    }

    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // The queue is based on MIN-heap
    // so an element with a smallest value
    // has a higher priority
    PriorityQueue<HuffmanNode*> toProcess;

    for (int ch: freqTable) {
        toProcess.add(new HuffmanNode(ch, freqTable[ch]), freqTable[ch]);
    }

    while (toProcess.size() != 1) {
        HuffmanNode* n1 = toProcess.dequeue();
        HuffmanNode* n2 = toProcess.dequeue();
        int count = n1->count + n2->count;
        HuffmanNode* combination = new HuffmanNode(NOT_A_CHAR, count, n1, n2);
        toProcess.add(combination, count);
    }

    return toProcess.dequeue();
}

void traverseTreeAndFillEncodingMap(HuffmanNode* encodingTree, const string& code, Map<int, string>& map) {
    if (encodingTree == nullptr) {
        return;
    } else if (encodingTree->character != NOT_A_CHAR) {
        map.add(encodingTree->character, code);
    } else {
        traverseTreeAndFillEncodingMap(encodingTree->zero, code + "0", map);
        traverseTreeAndFillEncodingMap(encodingTree->one, code + "1", map);
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    traverseTreeAndFillEncodingMap(encodingTree, "", encodingMap);
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
