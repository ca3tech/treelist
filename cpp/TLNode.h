#pragma once

template <typename T>
class TLNode {
    public:
        TLNode(unsigned int i, T& data) : i(i), data(data), depth_(1), parent(nullptr), left_(nullptr), right_(nullptr) {};
        unsigned int i;
        T& data;
        TLNode<T>* parent;
        TLNode<T>* left();
        void left(TLNode<T>*);
        TLNode<T>* right();
        void right(TLNode<T>*);
        int depth();
        int leftDepth();
        int rightDepth();
        TLNode<T>* grandparent();
        bool operator==(TLNode);
        bool operator!=(TLNode);
    private:
        int depth_;
        TLNode<T>* left_;
        TLNode<T>* right_;
        void updateDepth();
};

template <typename T>
int TLNode<T>::depth() {
    return depth_;
}

template <typename T>
void TLNode<T>::updateDepth() {
    depth_ = 1 + leftDepth() + rightDepth();
    if(parent != nullptr) {
        parent->updateDepth();
    }
}

template <typename T>
int TLNode<T>::leftDepth() {
    return (left_ == nullptr) ? 0 : left_->depth();
}

template <typename T>
int TLNode<T>::rightDepth() {
    return (right_ == nullptr) ? 0 : right_->depth();
}

template <typename T>
TLNode<T>* TLNode<T>::grandparent() {
    TLNode<T>* gp = nullptr;
    if(parent != nullptr) {
        gp = parent->parent;
    }
    return gp;
}

template <typename T>
TLNode<T>* TLNode<T>::left() {
    return left_;
}

template <typename T>
void TLNode<T>::left(TLNode<T>* node) {
    left_ = node;
    updateDepth();
}

template <typename T>
TLNode<T>* TLNode<T>::right() {
    return right_;
}

template <typename T>
void TLNode<T>::right(TLNode<T>* node) {
    right_ = node;
    updateDepth();
}

template <typename T>
bool TLNode<T>::operator==(TLNode<T> other) {
    return i == other.i && data == other.data;
}

template <typename T>
bool TLNode<T>::operator!=(TLNode<T> other) {
    return ! (*this == other);
}