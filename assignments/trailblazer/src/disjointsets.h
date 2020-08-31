#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

#include "set.h"

template <class ElementType>
class DisjointSets {
public:
    virtual void makeSet(ElementType* element) = 0;
    virtual const ElementType* findSet(const ElementType* element) const = 0;
    virtual void unionSets(const ElementType* el1, const ElementType* el2) = 0;
};

template <class ElementType>
class LinkedListDisjointSets : public DisjointSets<ElementType> {
public:
    void makeSet(ElementType* element) override;
    const ElementType* findSet(const ElementType* element) const override;
    void unionSets(const ElementType* el1, const ElementType* el2) override;

private:
    struct LinkedList;

    struct LinkedListNode {
        ElementType* element;
        LinkedListNode* next;
        LinkedList* parent;
    };

    struct LinkedList {
        LinkedListNode* head;
        LinkedListNode* tail;
        int size;
    };

    Set<LinkedList*> sets_;
    Map<const ElementType*, LinkedListNode*> nodeLookup_;

    void unionSets(LinkedList* set1, LinkedList* set2) const;
};

template <class ElementType>
void LinkedListDisjointSets<ElementType>::makeSet(ElementType* element) {
    auto list = new LinkedList();
    auto listNode = new LinkedListNode {element, nullptr, list};
    list->head = listNode;
    list->tail = listNode;
    list->size = 1;
    sets_.add(list);
    nodeLookup_[element] = listNode;
}

template <class ElementType>
const ElementType* LinkedListDisjointSets<ElementType>::findSet(const ElementType* element) const {
    LinkedListNode* listNode = nodeLookup_[element];
    LinkedList* list = listNode->parent;
    return list->head->element;
}

template <class ElementType>
void LinkedListDisjointSets<ElementType>::unionSets(const ElementType* el1, const ElementType* el2) {
    LinkedListNode* node1 = nodeLookup_[el1];
    LinkedListNode* node2 = nodeLookup_[el2];
    LinkedList* list1 = node1->parent;
    LinkedList* list2 = node2->parent;

    if (list2->size < list1->size) {
        unionSets(list1, list2);
    } else {
        unionSets(list2, list1);
    }
}

template <class ElementType>
void LinkedListDisjointSets<ElementType>::unionSets(LinkedList* set1, LinkedList* set2) const {
    for (LinkedListNode* curr = set2->head; curr != nullptr; curr = curr->next) {
        curr->parent = set1;
    }

    set1->tail->next = set2->head;
    set1->tail = set2->tail;
    set1->size += set2->size;
    delete set2;
}

#endif // DISJOINTSETS_H
