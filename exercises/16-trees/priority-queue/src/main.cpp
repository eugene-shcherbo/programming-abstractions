#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "priorityqueue.h"

using namespace std;

int main() {
    collections::PriorityQueue<string> pqueue;
    assert(pqueue.isEmpty());

    pqueue.enqueue("Richard", 5);
    pqueue.enqueue("Susan", 2);
    pqueue.enqueue("Edison", 1);

    assert(pqueue.peek() == "Edison");
    assert(pqueue.dequeue() == "Edison");
    assert(pqueue.peek() == "Susan");
    assert(pqueue.dequeue() == "Susan");
    assert(pqueue.peek() == "Richard");
    assert(pqueue.dequeue() == "Richard");
    assert(pqueue.isEmpty());

    return 0;
}
