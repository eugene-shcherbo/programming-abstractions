#pragma once
#include "pqueue.h"
#include <string>

class LinkedListPQueue : public PQueue {
public:
	LinkedListPQueue();
	~LinkedListPQueue();
	
    static LinkedListPQueue* merge(LinkedListPQueue* one, LinkedListPQueue* two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    const std::string& peek() const;
	
private:
    struct Node {
        std::string val;
        Node* next;
        Node* prev;
    };

    Node* head_;

    void clear();
};
