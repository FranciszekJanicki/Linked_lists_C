#include "CircularLinkedList.h"

template <class T>
CircularLinkedList<T>::CircularLinkedList() {

}

template <class T>
CircularLinkedList<T>::~CircularLinkedList() {

    for (int i = 0; i < length; ++i) {
        deleteNodeHead();
    }

    if (head != nullptr) delete head;
    if (tail != nullptr) delete tail;
}

template <class T>
// dont have to be ptrs to ptrs as i dont change what ptrs are pointing at, just what
// ptrs being members of ptrs are pointing at
void CircularLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {

    Node<T> *newest = nullptr;

    if (left != right) {
        newest = new Node<T>();
        newest->data = data;
        newest->next = right;
        left->next = newest;
    }

    ++length;
}

template <class T>
void CircularLinkedList<T>::addNodeHead(const T &data) {

    Node<T> *newest = new Node<T>();

    newest->data = data;
    newest->next = head;
    head = newest;

    ++length;
}

template <class T>
void CircularLinkedList<T>::addNodeTail(const T &data) {

    Node<T> *newest = nullptr;

    // if list empty
    if (tail == nullptr) {
        newest = new Node<T>();
        newest->data = data;
        newest->next = head;
        tail = newest;
    } 
    // not empty
    else {
        newest = new Node<T>();
        newest->data = data;
        newest->next = head;
        tail->next = newest;
        tail = newest;
    }

    ++length;
}

template <class T>
void CircularLinkedList<T>::deleteNodeTail() {
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
    // find second to last 
    Node<T> *current = head;
    for (int i = 0; i < length - 1; ++i) {
        current = current->next;
    }
    */

    tail = current;
    free(tail->next);
    tail->next = head;

    current = nullptr;
    --length;
}

template <class T>
void CircularLinkedList<T>::deleteNodeHead() {
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
void CircularLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (length == 0 && index == 0) addNodeHead(data); 
    else if (length == index) addNodeTail(data);
    else {
        int i = 0;
        Node<T> *current = head;
        Node<T> *previous = nullptr;

        for (i; i < index; ++i) {
            previous = current;
            current = current->next;
        }
        insertBetween(previous, current, data);
    }

    // OR
    /* 
    int i = 0;
    current = head;
    previous = nullptr;

    while (current != nullptr) {
        if (i == index) {
            if (current == head) addNodeHead(data);
            else if (current == tail) addNodetail(data);
            else {
                insertBetween(previous, current, data);
            }
            return; // stop iterating
        }
        previous = current;
        current = current->next;
        ++i;
    }
    */

    // OR
    /*
    current = getNode(index);
    previous = getNode(index - 1);
    insertBetween(previous, current, data);
    */

   previous = nullptr;
   current = nullptr;
}

template <class T>
void CircularLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = head;
    Node<T> *previous = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (i == index) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                previous->next = current->next;
                delete current;
            }
            return; // stop iterating
        }

        previous = current;
        current = current->next;
        ++i;
    }

    // OR
    /*
    current = getNode(index);
    previous = getNode(index - 1);
    previous->next = current->next;
    delete current;
    */

   // OR
   /*
    current = getNode(index + 1);
    previous = getNode(index - 1);
    delete previous->next;
    previous->next = current;
   */

    previous = nullptr;
    current = nullptr;
}

template <class T>
void CircularLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = head;
    Node<T> *previous = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                previous->next = current->next;
                delete current;
            }
            // return; // dont stop iterating, remove all nodes with this data
        }

        previous = current;
        current = current->next;
    }

    previous = nullptr;
    current = nullptr;
}

template <class T>
void CircularLinkedList<T>::print() const {
    // if list empty, avoid dereferencing nullptr
    if (head != nullptr) {
        Node<T> *current = head;
        for (int i = 0; i < length; ++i) {
            printf(nullptr, current->data);
            current = current->next;
        }
        current = nullptr;
    }
}

template <class T>
int CircularLinkedList<T>::getLength() const {
    return length;
}

template <class T>
T *CircularLinkedList<T>::getHead() const {
    return head;
}

template <class T>
T *CircularLinkedList<T>::getTail() const {
    return tail;
}

template <class T>
Node<T> *CircularLinkedList<T>::getNode(const int &index) const {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return nullptr;

    Node<T> *current = head;
    int i = 0;

    while (i < index) {
        current = current->next;
        ++i;
    }
    return current;
}

template <class T>
T CircularLinkedList<T>::getData(const int &index) const {
    return getNode(index)->data;
}