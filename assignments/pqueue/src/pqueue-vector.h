#pragma once
#include "pqueue.h"
#include <string>
#include "vector.h"

class VectorPQueue : public PQueue {
public:
	VectorPQueue();
	~VectorPQueue();
	
    static VectorPQueue* merge(VectorPQueue* one, VectorPQueue* two);
	
    void enqueue(const std::string& elem);
    std::string extractMin();
    const std::string& peek() const;
	
private:
    Vector<std::string> items_;

    int findMinIndex() const;
};
