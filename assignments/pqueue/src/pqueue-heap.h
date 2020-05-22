#pragma once
#include "pqueue.h"
#include <string>

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
    static HeapPQueue* merge(HeapPQueue* one, HeapPQueue* two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    const std::string& peek() const;
    
private:
    unsigned long capacity_;
    std::string* elements_;

    void minHeapify(int index);
    void extendCapacity();
    void add(std::string el);
};
