#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "pqueue.h"
using namespace std;

int main() {
    collections::PriorityQueue<string> visitors;
    visitors.enqueue("Mr. Smith", 5);
    visitors.enqueue("Mrs. Smith", 2.5);
    visitors.enqueue("Alan Rice", 7);
    visitors.enqueue("Hue Jackman", 7);
    visitors.enqueue("Alice Monroe", 1);
    visitors.enqueue("Elizabeth Doe", 3);
    visitors.enqueue("Jack Vorobey", 10);

    assert(visitors.dequeue() == "Alice Monroe");
    assert(visitors.dequeue() == "Mrs. Smith");
    assert(visitors.dequeue() == "Elizabeth Doe");
    assert(visitors.dequeue() == "Mr. Smith");
    assert(visitors.dequeue() == "Alan Rice");
    assert(visitors.dequeue() == "Hue Jackman");
    assert(visitors.dequeue() == "Jack Vorobey");

    cout << "All the tests are passed." << endl;

    return 0;
}
