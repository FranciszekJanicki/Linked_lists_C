#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include <stdio.h>

template <class T>
struct Node {
    Node *next = nullptr;
    Node *prev = nullptr;
    T data;
};

template <class T>
class DoublyCircularLinkedList {
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
        int capacity = 0;
        int size = 0;

        /* private methods as they do not have exception handling and should be run only inside other methods that do have it*/
        void insertEmptyBetween(Node<T> *left, Node<T> *right, Node<T>* &newest);
        void insertBetween(Node<T> *left, Node<T> *right, const T &data);
        void removeBetween(Node<T> *left, Node<T> *right);
        void addEmptyNodeTail(Node<T>* &newest);
        void addEmptyNodeHead(Node<T>* &newest);

    public:
        DoublyCircularLinkedList();
        ~DoublyCircularLinkedList();

        void addNodeHead(const T &data);
        void addNodeTail(const T &data);
        void deleteNodeTail();
        void deleteNodeHead();
        void insertNode(const int &index, const T &data);
        void removeNode(const T &index);
        void removeNodeElement(const T &data);
        void print() const;
        int getCapacity() const;
        int getSize() const;
        T *getHead() const;
        T *getTail() const;
        Node<T> *getNode(const int &index) const;
        T getData(const int &index) const;
        void setData(const int &index, const T &data);
        void assign(const T *array, const int &length);
};



#endif
