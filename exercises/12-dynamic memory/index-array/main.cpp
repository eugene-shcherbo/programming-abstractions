#include <iostream>
using namespace std;

int* createIndexArray(int size);
void printArr(int arr[], int size);

constexpr int SIZE = 10;

int main() {
    int* indexArr = createIndexArray(SIZE);
    printArr(indexArr, SIZE);

    delete[] indexArr;

    return 0;
}

int* createIndexArray(int size) {
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        *(arr + i) = i;
    }

    return arr;
}

void printArr(int arr[], int size) {
    cout << "{";

    if (size > 0) {
        cout << arr[0];

        for (int i = 1; i < size; i++) {
            cout << ", " << arr[i];
        }
    }

    cout << "}";
}
