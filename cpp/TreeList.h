#pragma once

#include "TLNode.h"
#include "TreeListIterator.h"

template <class T>
class TreeList {
public:
    TreeList();
    ~TreeList();
    T* operator[] (unsigned int);
    int length();
    int max();
    int min();
    T* remove(unsigned int);
    void set(unsigned int, T&);
    TreeListIterator<T> begin();
    TreeListIterator<T> end();
    TreeListIterator<T> rbegin();
    TreeListIterator<T> rend();
protected:
    TLNode<T>* head;
    TLNode<T>* root;
    TLNode<T>* tail;
private:
    TLNode<T>* findNode(unsigned int, TLNode<T>*);
    void insert(unsigned int, T&, TLNode<T>*);
    void insert(TLNode<T>*, TLNode<T>*);
    void balance(TLNode<T>*);
    void lrotate(TLNode<T>*);
    void rrotate(TLNode<T>*);
    void updateMinMax(TLNode<T>*);
};

// The linker complains if I don't define the implementation in this file
 
template <class T>
TreeList<T>::TreeList() : head(nullptr), root(nullptr), tail(nullptr) {};

template <class T>
TreeList<T>::~TreeList() {
    if(root != nullptr) {
        // Actually I need to walk the tree and remove all references
        delete root;
    }
};

template <class T>
T* TreeList<T>::operator[] (unsigned int i) {
    T* data = nullptr;
    if(root != nullptr) {
        TLNode<T>* node = findNode(i, root);
        if(node != nullptr) {
            data = &(node->data);
        }
    }
    return data;
}

template <class T>
int TreeList<T>::length() {
    return max() + 1;
}

template <class T>
int TreeList<T>::max() {
    return (tail == nullptr) ? -1 : tail->i;
}

template <class T>
int TreeList<T>::min() {
    return (head == nullptr) ? -1 : head->i;
}

template <class T>
void TreeList<T>::set(unsigned int i, T& data) {
    if(root == nullptr) {
        root = new TLNode<T>(i, data);
        updateMinMax(root);
    } else {
        TLNode<T>* curnode = findNode(i, root);
        if(curnode == nullptr) {
            insert(i, data, root);
        } else {
            curnode->data = data;
        }
    }
};

template <class T>
T* TreeList<T>::remove(unsigned int i) {
    T* item = nullptr;
    TLNode<T>* node = findNode(i, root);
    if(node != nullptr) {
        item = &(node->data);
        if(node == root && node->depth() == 1) {
            root = nullptr;
        } else {
            TLNode<T>* rnode;
            TLNode<T>* inode;
            if(node == root) {
                if(node->leftDepth() >= node->rightDepth()) {
                    root = node->left();
                    inode = node->right();
                } else {
                    root = node->right();
                    inode = node->left();
                }
                root->parent = nullptr;
                rnode = root;
            } else {
                TLNode<T>* pnode = node->parent;
                if(node == pnode->left()) {
                    pnode->left(node->left());
                    rnode = node->left();
                    inode = node->right();
                } else {
                    pnode->right(node->right());
                    rnode = node->right();
                    inode = node->left();
                }
            }
            if(inode != nullptr) {
                insert(inode, rnode);
            }
        }
        delete node;
    }
    return item;
}

template <typename T>
TreeListIterator<T> TreeList<T>::begin() {
    return TreeListIterator<T>(head);
}

template <typename T>
TreeListIterator<T> TreeList<T>::end() {
    return TreeListIterator<T>(nullptr);
}

template <typename T>
TreeListIterator<T> TreeList<T>::rbegin() {
    return TreeListIterator<T>(tail, true);
}

template <typename T>
TreeListIterator<T> TreeList<T>::rend() {
    return TreeListIterator<T>(nullptr);
}

// Private members

template <class T>
TLNode<T>* TreeList<T>::findNode(unsigned int i, TLNode<T>* curnode) {
    TLNode<T>* node = nullptr;
    if(curnode->i == i) {
        node = curnode;
    } else if(curnode->i > i && curnode->left() != nullptr) {
        node = findNode(i, curnode->left());
    } else if(curnode->right() != nullptr) {
        node = findNode(i, curnode->right());
    }
    return node;
}

template <class T>
void TreeList<T>::insert(unsigned int i, T& data, TLNode<T>* curnode) {
    insert(new TLNode<T>(i, data), curnode);
}

template <class T>
void TreeList<T>::insert(TLNode<T>* inode, TLNode<T>* curnode) {
    if(curnode->i == inode->i) {
        curnode->data = inode->data;
    } else if(curnode->i > inode->i) {
        if(curnode->left() == nullptr) {
            curnode->left(inode);
            inode->parent = curnode;
            updateMinMax(inode);
            balance(curnode->left());
        } else {
            insert(inode, curnode->left());
        }
    } else if(curnode->right() == nullptr) {
        curnode->right(inode);
        inode->parent = curnode;
        updateMinMax(inode);
        balance(curnode->right());
    } else {
        insert(inode, curnode->right());
    }
}

template <class T>
void TreeList<T>::balance(TLNode<T>* node) {
    TLNode<T>* gp = node->grandparent();
    if(gp != nullptr && gp->depth() > 2) {
        if(gp->leftDepth() > gp->rightDepth()) {
            rrotate(gp);
        } else if(gp->rightDepth() > gp->leftDepth()) {
            lrotate(gp);
        } else if(node->parent != nullptr) {
            balance(node->parent);
        }
    }
}

template <class T>
void TreeList<T>::lrotate(TLNode<T>* node) {
    TLNode<T>* curnode = node->right();
    curnode->parent = node->parent;
    if(node == root) {
        root = curnode;
    }
    node->right(nullptr);
    while(curnode->left() != nullptr) {
        curnode = curnode->left();
    }   
    curnode->left(node);
    node->parent = curnode;
    balance(node);
}

template <class T>
void TreeList<T>::rrotate(TLNode<T>* node) {
    TLNode<T>* curnode = node->left();
    curnode->parent = node->parent;
    if(node == root) {
        root = curnode;
    }
    node->left(nullptr);
    if(curnode->right() == nullptr) {
        curnode->right(node);
    } else {
        curnode = curnode->right();
        while(curnode->left() != nullptr) {
            curnode = curnode->left();
        }
        curnode->left(node);
    }
    node->parent = curnode;
    balance(node);
}

template <class T>
void TreeList<T>::updateMinMax(TLNode<T>* node) {
    if(head == nullptr || node->i < head->i) {
        head = node;
    }
    if(tail == nullptr || node->i > tail->i) {
        tail = node;
    }
}