#include <iostream>
#include "vector.h"
#include "set.h"
#include "domino.h"
#include "console.h"

using namespace std;

bool formsDominoChain(const Vector<Domino>& dominos);
bool dominoChainHelper(const Vector<Domino>& dominos, Vector<Domino>& chain, Set<Domino>& used);
bool match(const Domino& left, const Domino& right);

int main() {
    Domino twoSix(2, 6);
    Domino oneSix(1, 6);
    Domino oneFour(1, 4);
    Domino threeFour(3, 4);

    Vector<Domino> success {
        twoSix, oneSix, oneFour, threeFour
    };

    if (formsDominoChain(success)) {
        cout << "dominos " << success << " can be chained together" << endl;
    }

    return 0;
}

bool formsDominoChain(const Vector<Domino>& dominos) {
    Vector<Domino> chain;
    Set<Domino> used;
    return dominoChainHelper(dominos, chain, used);
}

bool dominoChainHelper(const Vector<Domino>& dominos, Vector<Domino>& chain, Set<Domino>& used) {
    if (chain.size() == dominos.size()) {
        return true;
    }

    for (const Domino& dom: dominos) {
        if (!used.contains(dom) && (used.isEmpty() || match(dom, chain.back()))) {
            used.add(dom);
            chain.add(dom);

            if (dominoChainHelper(dominos, chain, used)) {
                return true;
            }

            used.remove(dom);
            chain.removeBack();
        }
    }

    return false;
}

bool match(const Domino& left, const Domino& right) {
    return left.getRightDots() == right.getLeftDots()
            || left.getRightDots() == right.getRightDots()
            || left.getLeftDots() == right.getLeftDots()
            || left.getLeftDots() == right.getRightDots();
}

