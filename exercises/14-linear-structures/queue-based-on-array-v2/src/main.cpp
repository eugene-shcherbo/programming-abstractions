#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "queue.h"
using namespace std;

int main() {
    collections::Queue<string> strings;
    assert(strings.isEmpty());
    assert(strings.size() == 0);
    strings.enqueue("hello world");
    strings.enqueue("bye bye");
    assert(strings.size() == 2);

    assert(strings.dequeue() == "hello world");
    assert(strings.dequeue() == "bye bye");
    assert(strings.isEmpty());

    collections::Queue<int> values;

    for (int i = 0; i < 10; i++) {
        values.enqueue(i);
    }
    assert(values.size() == 10);
    values.dequeue();
    values.dequeue();
    assert(values.size() == 8);
    values.enqueue(100500);
    assert(values.size() == 9);

    for (int i = 2; i < 10; i++) {
        assert(values.peek() == i);
        assert(values.dequeue() == i);
    }
    assert(values.peek() == 100500);
    assert(values.dequeue() == 100500);
    assert(values.isEmpty());

    collections::Queue<string> greeting;
    greeting.enqueue("Zhenya.");
    greeting.enqueue("am ");
    greeting.enqueue("I ");
    greeting.enqueue("Hello, ");
    greeting.reverse();

    string greetingStr;
    while (!greeting.isEmpty()) {
        greetingStr += greeting.dequeue();
    }
    assert(greetingStr == "Hello, I am Zhenya.");

    cout << "All the tests are passes sucessfully.." << endl;

    return 0;
}
