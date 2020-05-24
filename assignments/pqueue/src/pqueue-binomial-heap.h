#pragma once
#include <string>
#include "pqueue.h"
#include "vector.h"

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
    static BinomialHeapPQueue* merge(BinomialHeapPQueue* one, BinomialHeapPQueue* two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    const std::string& peek() const;
	
private:
    struct Node {
        std::string elem;
        Vector<Node*> children;
    };

    Vector<Node*> heap_;

    int findMinIndex() const;
    void clear(Node* tree);
    static Node* mergeTrees(Node* lTree, Node* rTree);
    static void mergeHeaps(Vector<Node*>& one, Vector<Node*>& two, Vector<Node*>& res);
};

