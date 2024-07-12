#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>

template <class T>
struct Node {
    Node *next = nullptr;
    Node *prev = nullptr;
    T data;
};

template <class T>
class DoublyLinkedList {
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        int length = 0;
        void insertBetween(Node<T> *left, Node<T> *right, const T &data);

    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

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
        Node<T> *getNode(const int &index) const;
        T getData(const int &index) const;
};

#endif