#include <iostream>
#include "vector.h"
#include "console.h"

using namespace std;

constexpr int MINIMUM_PRIME_NUM = 2;

void generatePrimes(Vector<int>& primes, int upperBound);
void initSieve(Vector<int>& sieve, int upperBound);
void cleanSieve(Vector<int>& sieve, int divider);

int main() {
    Vector<int> primes;
    generatePrimes(primes, 1000);

    cout << "Count = " << primes.size() << endl;
    cout << "Primes " << primes << endl;

    return 0;
}

void generatePrimes(Vector<int>& primes, int upperBound) {
    initSieve(primes, upperBound);

    for (int i = 0; i < primes.size(); ++i) {
        cleanSieve(primes, primes[i]);
    }
}

void initSieve(Vector<int>& sieve, int upperBound) {
    sieve.clear();
    for (int i = MINIMUM_PRIME_NUM; i <= upperBound; ++i) {
        sieve.add(i);
    }
}

void cleanSieve(Vector<int>& sieve, int divider) {
    for (int i = sieve.size() - 1; sieve[i] > divider; --i) {
        if (sieve[i] % divider == 0) {
            sieve.remove(i);
        }
    }
}
