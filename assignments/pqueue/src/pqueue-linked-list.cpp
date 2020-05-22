#include "pqueue-linked-list.h"
using namespace std;

LinkedListPQueue::LinkedListPQueue() {
    head_ = nullptr;
}

LinkedListPQueue::~LinkedListPQueue() {
    clear();
}

const string& LinkedListPQueue::peek() const {
    if (isEmpty()) {
        throw "error: attempting to get a peek of the empty queue";
    } else {
        return head_->val;
    }
}

string LinkedListPQueue::extractMin() {
    if (isEmpty()) {
        throw "error: attempting to get a peek of the empty queue";
    } else {
        string res = peek();
        Node* old = head_;
        head_ = head_->next;
        delete old;
        logSize--;
        return res;
    }
}

void LinkedListPQueue::enqueue(const string& el) {
    Node* newNode = new Node { el, nullptr, nullptr };

    if (isEmpty()) {
        head_ = newNode;
    } else if (head_->val > el) {
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
    } else {
        Node* curr = head_;
        while (curr->next != nullptr && curr->next->val <= el) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next = newNode;

        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }
    }

    logSize++;
}

LinkedListPQueue* LinkedListPQueue::merge(LinkedListPQueue* one, LinkedListPQueue* two) {
    Node* left = one == nullptr ? nullptr : one->head_;
    Node* right = two == nullptr ? two->head_ : two->head_;

    LinkedListPQueue* res = new LinkedListPQueue();
    Node* resTail = res->head_;

    while (left != nullptr || right != nullptr) {
        string min = "";
        if (left == nullptr) {
            min = right->val;
            right = right->next;
        } else if (right == nullptr) {
            min = left->val;
            left = left->next;
        } else if (left->val < right->val) {
            min = left->val;
            left = left->next;
        } else {
            min = right->val;
            right = right->next;
        }

        Node* newNode = new Node { min, nullptr, nullptr };
        if (resTail == nullptr) {
            res->head_ = newNode;
        } else {
            resTail->next = newNode;
            newNode->prev = resTail;
        }
        resTail = newNode;
        res->logSize++;
    }

    return res;
}

void LinkedListPQueue::clear() {
    Node* curr = head_;
    while (curr != nullptr) {
        head_ = head_->next;
        delete curr;
        curr = head_;
    }
}
