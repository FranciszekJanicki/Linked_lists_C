#ifndef NODE_H
#define NODE_H


template <typename T>
struct Node {
    Node<T> *next = nullptr;
    Node<T> *prev = nullptr;
    T data;
};


#endif // NODE_H
