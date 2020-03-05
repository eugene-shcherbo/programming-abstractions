#include <iostream>
#include "stack.h"
#include "queue.h"
#include "console.h"

using namespace std;

void reverseQueue(Queue<string>& queue);
void testReverseQueue(const Queue<string>& queue, const Queue<string>& expected);

int main() {
    Queue<string> queue;

    queue.enqueue("string1");
    queue.enqueue("string2");
    queue.enqueue("string3");

    Queue<string> reversed;

    reversed.enqueue("string3");
    reversed.enqueue("string2");
    reversed.enqueue("string1");

    testReverseQueue(queue, reversed);
    testReverseQueue(Queue<string>(), Queue<string>());

    return 0;
}

void testReverseQueue(const Queue<string>& queue, const Queue<string>& expected) {
    Queue<string> actual = queue;
    reverseQueue(actual);

    cout << "Reversed queue is " << queue << endl;
    cout << "Result: " << (actual == expected ? "Success." : "Failed") << endl;
}

void reverseQueue(Queue<string>& queue) {
    Stack<string> values;

    while (!queue.isEmpty()) {
        values.push(queue.dequeue());
    }

    while (!values.isEmpty()) {
        queue.enqueue(values.pop());
    }
}
