#include "encoding.h"
#include "priorityqueue.h"
#include "filelib.h"

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

void writeBits(const string& bits, obitstream& output) {
    for (char b: bits) {
        int bit = b == '1' ? 1 : 0;
        output.writeBit(bit);
    }
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    while (true) {
        int ch = input.get();
        if (ch == EOF) {
            break;
        } else {
            writeBits(encodingMap[ch], output);
        }
    }
    writeBits(encodingMap[PSEUDO_EOF], output);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* curr = encodingTree;
    constexpr int EndOfBitStream = -1;
    int bit;
    while ((bit = input.readBit()) != EndOfBitStream) {
        if (bit == 1) curr = curr->one;
        else curr = curr->zero;

        if (curr->character == PSEUDO_EOF) {
            break;
        } else if (curr->character != NOT_A_CHAR) {
            output.put(curr->character);
            curr = encodingTree;
        }
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);
    output << frequencyTable;
    rewindStream(input);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> frequencyTable;
    input >> frequencyTable;
    HuffmanNode* encodingTree = buildEncodingTree(frequencyTable);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    if (node == nullptr) return;

    if (!node->isLeaf()) {
        freeTree(node->one);
        freeTree(node->zero);
    }

    delete node;
}
