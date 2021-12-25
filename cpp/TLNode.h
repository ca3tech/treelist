#pragma once

template <typename T>
struct TLNode {
    TLNode(unsigned int i, T& data) : i(i), data(data), parent(nullptr), left(nullptr), right(nullptr) {};
    unsigned int i;
    T& data;
    TLNode<T>* parent;
    TLNode<T>* left;
    TLNode<T>* right;
    int depth();
    int leftDepth();
    int rightDepth();
    TLNode<T>* grandparent();
};

template <typename T>
int TLNode<T>::depth() {
    int d = 1;
    int ld = leftDepth();
    int rd = rightDepth();
    if(ld >= rd) {
        d += ld;
    } else if(rd > ld) {
        d += rd;
    }
    return d;
}

template <typename T>
int TLNode<T>::leftDepth() {
    int d = 0;
    if(left != nullptr) {
        d = left->depth();
    }
    return d;
}

template <typename T>
int TLNode<T>::rightDepth() {
    int d = 0;
    if(right != nullptr) {
        d = right->depth();
    }
    return d;
}

template <typename T>
TLNode<T>* TLNode<T>::grandparent() {
    TLNode<T>* gp = nullptr;
    if(parent != nullptr) {
        gp = parent->parent;
    }
    return gp;
}