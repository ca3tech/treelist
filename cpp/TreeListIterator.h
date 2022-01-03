#include <cstddef>
#include <iterator>
#include <queue>
#include <set>
#include "TLNode.h"

using namespace std;

template <typename T>
class TreeListIterator {
public:
    using iterator_category = input_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

    TreeListIterator(TLNode<T>*);
    TreeListIterator(TLNode<T>*, bool);
    T& operator*();
    T* operator->();
    bool operator==(const TreeListIterator&);
    bool operator!=(const TreeListIterator&);
    // prefix increment
    TreeListIterator<T>& operator++();
    // postfix increment
    TreeListIterator<T> operator++(int);

private:
    TLNode<T>* head;
    bool rev;
    TLNode<T>* curnode;
    queue<TLNode<T>*> nq;
    void buildQueue(TLNode<T>*, set<TLNode<T>*>*);
};

template <typename T>
TreeListIterator<T>::TreeListIterator(TLNode<T>* node) : TreeListIterator(node, false) {}

template <typename T>
TreeListIterator<T>::TreeListIterator(TLNode<T>* node, bool reverse) {
    head = node;
    rev = reverse;
    buildQueue(head, new set<TLNode<T>*>());
    ++(*this);
}

template <typename T>
T& TreeListIterator<T>::operator*() {
    return curnode->data;
};

template <typename T>
T* TreeListIterator<T>::operator->() {
    return *(curnode->data);
};

template <typename T>
bool TreeListIterator<T>::operator==(const TreeListIterator& other) {
    return curnode == other.curnode ||
           (curnode != nullptr && other.curnode != nullptr && *curnode == *other.curnode);
};

template <typename T>
bool TreeListIterator<T>::operator!=(const TreeListIterator& other) {
    return ! (*this == other);
};

template <typename T>
TreeListIterator<T>& TreeListIterator<T>::operator++() {
    if(nq.size() > 0) {
        curnode = nq.front();
        nq.pop();
    } else {
        curnode = nullptr;
    }
    return (*this);
};

template <typename T>
TreeListIterator<T> TreeListIterator<T>::operator++(int) {
    TreeListIterator tmp = *this;
    ++(*this);
    return tmp;
};

template <typename T>
void TreeListIterator<T>::buildQueue(TLNode<T>* curnode, set<TLNode<T>*>* ignodes) {
    if(curnode) {
        bool doself = false;
        if(ignodes->count(curnode) == 0) {
            ignodes->insert(curnode);
            doself = true;
        }
        if(rev) {
            if(curnode->right() && ignodes->count(curnode->right()) == 0) {
                buildQueue(curnode->right(), ignodes);
            }
        } else if(curnode->left() && ignodes->count(curnode->left()) == 0) {
            buildQueue(curnode->left(), ignodes);
        }
        if(doself) {
            nq.push(curnode);
        }
        if(rev) {
            if(curnode->left() && ignodes->count(curnode->left()) == 0) {
                buildQueue(curnode->left(), ignodes);
            }
        } else if(curnode->right() && ignodes->count(curnode->right()) == 0) {
            buildQueue(curnode->right(), ignodes);
        }
        buildQueue(curnode->parent, ignodes);
        if(doself) {
            ignodes->erase(curnode);
        }
    }
}