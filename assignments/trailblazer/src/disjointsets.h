#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

#include "set.h"
#include "hashmap.h"

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
    HashMap<const ElementType*, LinkedListNode*> nodeLookup_;

    void unionSets(LinkedList* set1, LinkedList* set2) const;
};

template <class ElementType>
class DisjointSetsForest : public DisjointSets<ElementType> {

public:
    void makeSet(ElementType* element) override;
    const ElementType* findSet(const ElementType* element) const override;
    void unionSets(const ElementType* el1, const ElementType* el2) override;

private:
    struct TreeNode {
        const ElementType* element;
        TreeNode* parent;
        int rank;
    };

    HashMap<const ElementType*, TreeNode*> nodeLookup_;
    TreeNode* findSet(TreeNode* element) const;
};

/* Linked List Disjoint Sets implementation */

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

/* Disjoint Sets Forest implementation */

template <class ElementType>
void DisjointSetsForest<ElementType>::makeSet(ElementType* element) {
    auto treeNode = new TreeNode { element };
    treeNode->parent = treeNode;
    treeNode->rank = 0;
    nodeLookup_[element] = treeNode;
}

template <class ElementType>
const ElementType* DisjointSetsForest<ElementType>::findSet(const ElementType* element) const {
    TreeNode* treeNode = nodeLookup_[element];
    return findSet(treeNode)->element;
}

template <class ElementType>
typename DisjointSetsForest<ElementType>::TreeNode* DisjointSetsForest<ElementType>::findSet(TreeNode* node) const {
    // is root?
    if (node != node->parent) {
        node->parent = findSet(node->parent);
    }
    return node->parent;
}

template <class ElementType>
void DisjointSetsForest<ElementType>::unionSets(const ElementType* el1, const ElementType* el2) {
    TreeNode* root1 = nodeLookup_[findSet(el1)];
    TreeNode* root2 = nodeLookup_[findSet(el2)];

    if (root1 == root2) return;

    if (root1->rank > root2->rank) {
        root2->parent = root1;
    } else {
        root1->parent = root2;
        if (root1->rank == root2->rank) root2->rank++;
    }
}

#endif // DISJOINTSETS_H
