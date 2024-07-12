#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdio.h>

template <class T>
struct Node {
    Node *next = nullptr;
    T data;
};

template <class T>
class SinglyLinkedList {
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        int length = 0;
        void insertBetween(Node<T> *left, Node<T> *right, const T &data);

    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void addNodeHead(const T &data);
        void addNodeTail(const T &data);
        void deleteNodeTail();
        void deleteNodeHead();
        void insertNode(const int &index, const T &data);
        void removeNode(const T &index);
        void removeNodeElement(const T &data);
        void print() const;
        int getLength() const;
        T *getHead() const;
        T *getTail() const;
        Node<T> *getNode(const int& index) const;
        T getData(const int& index) const;
};

#endif
