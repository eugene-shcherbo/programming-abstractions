#include <iostream>
#include "console.h"
#include "vector.h"

using namespace std;

int cutStock(const Vector<int>& requests, int stockLength);
bool isEnoughStock(Vector<int>& requests, Vector<int>& pipes);

int main() {
    Vector<int> requests { 4, 3, 4, 1, 7, 8 };

    cout << "Cut stock for these requests is "  << cutStock(requests, 8) << endl;

    return 0;
}

int cutStock(const Vector<int>& requests, int stockLength) {
    for (int request: requests) {
        if (request > stockLength) {
            throw "Pipe requested can't be longer than the stock length value";
        }
    }

    int pipesNumber = 0;
    Vector<int> r = requests;
    Vector<int> pipes;

    while (!isEnoughStock(r, pipes)) {
        pipesNumber++;
        pipes += stockLength;
    }

    return pipesNumber;
}

bool isEnoughStock(Vector<int>& requests, Vector<int>& pipes) {
    if (requests.isEmpty()) return true;

    int request = requests.removeBack();

    for (int& pipe: pipes) {
        if (request <= pipe) {
            pipe -= request;

            if (isEnoughStock(requests, pipes)) {
                return true;
            }

            pipe += request;
        }
    }

    requests.add(request);

    return false;
}
