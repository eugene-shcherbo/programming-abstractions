#include <iostream>

using namespace std;

struct ListNode {
    int data;
    ListNode* next;

    ListNode(int data, ListNode* next = nullptr) : data(data), next(next) {
    }
};

/**
 * @brief adds a new node with the given value to the list accessed by the given handle
 * in the position identified by index. Computanional Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 * @param value - a value of the node to be added
 * @param index - a position number where a new one should be placed
 */
void add(ListNode*& handle, int value, int index);

/**
 * @brief removes a node in the given index position. Computational Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 * @param index - a position number indicating a node to be removed
 */
void remove(ListNode*& handle, int index);

/**
 * @brief makes the list identified by the given handle into circular. Computational Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 */
void makeIntoCircular(ListNode* handle);

/**
 * @brief prints a linked list identified by a list handle. Computational Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 */
void print(ListNode* handle);

/**
 * @brief prints a circular list identified by the handle. The function assumes that
 * the list is circular therefore it doesn't make any checks. Computational Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 * @param n - how many times to cycle while printing the list
 */
void printCircular(ListNode* handle, int n);

/**
 * @brief returns a number of nodes in the linked lists. Computational Complexity: O(N)
 * @param handle - a pointer to the first node in the Linked List structure
 * @return a number of nodes in the structure
 */
int size(ListNode* handle);

/**
 * @brief prints a size of a linked list
 * @param handle - a pointer to the first node in the Linked List structure
 */
void printSize(ListNode* handle);

/**
 * @brief prints a number of elements in the list and its elements
 * @param handle - a pointer to the first node in the Linked List structure
 */
void printListState(ListNode* handle);

int main()
{
    ListNode* list = nullptr;
    printListState(list);

    add(list, 10, 0);
    add(list, 8, 0);
    add(list, 9, 1);
    add(list, 7, 0);
    add(list, 15, 2);
    printListState(list); // 7 -> 8 -> 15 -> 9 -> 10

    remove(list, 4);
    remove(list, 1);
    remove(list, 0);
    remove(list, 1);
    remove(list, 0);
    printListState(list); // No nodes

    add(list, 10, 0);
    add(list, 8, 0);
    add(list, 9, 1);
    add(list, 7, 0);
    add(list, 15, 2);
    printListState(list); // 7 -> 8 -> 15 -> 9 -> 10

    makeIntoCircular(list);
    printCircular(list, 2); // 7 -> 8 -> 15 -> 9 -> 10 -> 7 -> 8 -> 15 -> 9 -> 10
    cout << endl << endl;

    return 0;
}

void printListState(ListNode* handle) {
    printSize(handle);
    print(handle);
    cout << endl << endl;
}

void print(ListNode* handle) {
    if (handle == nullptr) {
        cout << "No nodes";
    } else {
        for (ListNode* current = handle; current != nullptr; current = current->next) {
            cout << current->data;

            if (current->next != nullptr) {
                cout << "->";
            }
        }
    }
}

void printCircular(ListNode* handle, int n) {
    if (handle == nullptr) {
        cout << "No nodes";
    } else {
        for (int i = n; i > 0; i--) {
            ListNode* curr = handle;
            do {
                cout << curr->data;
                curr = curr->next;

                if (curr != handle || i > 1) {
                    cout << "->";
                }
            } while (curr != handle);
        }
    }
}

void printSize(ListNode* handle) {
    int listSize = size(handle);
    cout << "List size " << listSize << endl;
}

int size(ListNode* handle) {
    int count = 0;
    for (ListNode* current = handle; current != nullptr; current = current->next) {
        count++;
    }
    return count;
}

void add(ListNode*& handle, int value, int index) {
    ListNode* newNode = new ListNode(value);

    if (index < 0 || index > size(handle)) {
        throw "add: invalid index";
    } else if (index == 0) {
        newNode->next = handle;
        handle = newNode;
    } else {
        ListNode* current = handle;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void remove(ListNode*& handle, int index) {
    if (index < 0 || index > size(handle) - 1) {
        throw "remove: invalid index";
    } else if (index == 0) {
        ListNode* trash = handle;
        handle = handle->next;
        delete trash;
    } else {
        ListNode* current = handle;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        ListNode* trash = current->next;
        current->next = trash->next;
        delete trash;
    }
}

void makeIntoCircular(ListNode* handle) {
    if (handle == nullptr) {
        return;
    }

    ListNode* curr = handle;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = handle;
}
