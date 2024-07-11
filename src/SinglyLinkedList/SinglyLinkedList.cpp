#include "SinglyLinkedList.h"

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {

}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {

    for (int i = 0; i < length; ++i) {
        deleteNodeHead();
    }

    if (head != nullptr) delete head;
    if (tail != nullptr) delete tail;
}

template <class T>
// dont have to be ptrs to ptrs as i dont change what ptrs are pointing at, just what
// ptrs being members of ptrs are pointing at
void SinglyLinkedList<T>::insertBetween(Node<T> *current, Node<T> *prev, const T &data) {

    Node<T> *newest = nullptr;

    if (current != prev) {
        newest = new Node<T>();
        newest->data = data;
        newest->next = current;
        prev->next = newest;
    }

    ++length;
}

template <class T>
void SinglyLinkedList<T>::addNodeHead(const T &data) {

    Node<T> *newest = new Node<T>();

    newest->data = data;
    newest->next = head;
    head = newest;

    ++length;
}

template <class T>
void SinglyLinkedList<T>::addNodeTail(const T &data) {

    Node<T> *newest = nullptr;

    // if list empty
    if (tail == nullptr) {
        newest = new Node<T>();
        newest->data = data;
        tail = newest;
    } 
    // not empty
    else {
        newest = new Node<T>();
        newest->data = data;
        tail->next = newest;
        tail = newest;
    }

    ++length;
}

template <class T>
void SinglyLinkedList<T>::deleteNodeTail() {
    // if list empty
    if (head == nullptr) return;

    // if list has 1 element
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // find second to last 
    Node<T> *current = head;
    while (current->next != tail) {
        current = current->next;
    }
    // OR
    /*
    // if list empty
    if (length == 0) return;

    // if list has 1 element
    if (length == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // find second to last 
    Node<T> *current = head;
    for (int i = 0; i < length - 1; ++i) {
        current = current->next;
    }
    */

    tail = current;
    free(tail->next);
    tail->next = nullptr;

    current = nullptr;
    --length;
}

template <class T>
void SinglyLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (length == 0) return;

    // if list has 1 element
    if (length == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    Node<T> *temp = head;
    head = head->next;
    delete temp;

    temp = nullptr;
    --length;
}

template <class T>
void SinglyLinkedList<T>::insertNode(const int &index, const T &data) {
    // if  tried to insert at incorrect index
    if (index < 0 || index > length) return;

    if (length == 0 && index == 0) addNodeHead(data); 
    else if (length == index) addNodeTail(data);
    else {
        int i = 0;
        Node<T> *current = head;
        Node<T> *prev = nullptr;

        while (i < index) {
            prev = current;
            current = current->next;
            ++i;
        }
        insertBetween(current, prev, data);
    }

    // OR
    /* 
    Node<T> *current = head;
    Node<T> *prev = nullptr;
    int i = 0;

    while (current != nullptr) {
        if (i == index) {
            if (current == head) addNodeHead(data);
            else if (current == tail) addNodetail(data);
            else {
                insertBetween(current, prev, data);
            }
            return; // stop iterating
        }
        prev = current;
        current = current->next;
    }
    */
}

template <class T>
void SinglyLinkedList<T>::removeNode(const T &index) {
    if (index < 0 || index > length) return;

    Node<T> *current = head;
    Node<T> *prev = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (i == index) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                prev->next = current->next;
                delete current;
            }
            return; // stop iterating
        }

        prev = current;
        current = current->next;
    }
}

template <class T>
void SinglyLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = head;
    Node<T> *prev = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == head) addNodeHead(data);
            else if (current == tail) addNodeTail(data);
            else {
                prev->next = current->next;
                delete current;
            }
            // return; // dont stop iterating, remove all nodes with this data
        }

        prev = current;
        current = current->next;
    }
}

template <class T>
void SinglyLinkedList<T>::print() const {
    Node<T> *current = head;
    for (int i = 0; i < length; ++i) {
        printf(nullptr, current->data);
        current = current->next;
    }
}

template <class T>
int SinglyLinkedList<T>::getLength() const {
    return length;
}

template <class T>
T *SinglyLinkedList<T>::getHead() const {
    return head;
}

template <class T>
T *SinglyLinkedList<T>::getTail() const {
    return tail;
}