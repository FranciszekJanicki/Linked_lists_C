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
void SinglyLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {

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
        newest->next = nullptr;
        tail = newest;
    } 
    // not empty
    else {
        newest = new Node<T>();
        newest->data = data;
        newest->next = nullptr;
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
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) addNodeHead(data); 
    else if (index == length) addNodeTail(data);
    else {

        // just need to find second to last to index (because you can calculate current (index) by previous->next)
        previous = getNode(index - 1);
        current = previous->next; // current = getNode(index);
        insertBetween(previous, current, data);

        // OR
        /*
        int i = 0;
        current = head;
        previous = nullptr;

        for (i; i < index; ++i) {
            previous = current;
            current = current->next;
        }
        insertBetween(previous, current, data);
        */
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

   previous = nullptr;
   current = nullptr;
}

template <class T>
void SinglyLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) deleteNodeHead(); // this function checks if length is 0
    else if (index == length) deleteNodeTail(); // this function checks if length is 0
    else {
        // just need to find second to last to index (because you can calculate current (index) by previous->next)
        previous = getNode(index - 1);
        current = previous->next; // current = getNode(index);

        previous->next = current->next;
        delete current;
        --length;

        // OR
        /*
        // just need to find second to last to index (because you can calculate index by previous->next and one after by current->next)
        previous = getNode(index - 1);
        current = (previous->next)->next;// current = getNode(index + 1); 
        delete previous->next;
        previous->next = current;
        --length;
        */
    }

    // OR
    /*
    int i = 0;
    current = head;
    while (current != nullptr) {
        
        if (i == index) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                previous->next = current->next;
                delete current;
                --length;
            }
            return; // stop iterating
        }

        previous = current;
        current = current->next;
        ++i;
    }
    */

    previous = nullptr;
    current = nullptr;
}

template <class T>
void SinglyLinkedList<T>::removeNodeElement(const T &data) {

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
                --length;
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
void SinglyLinkedList<T>::print() const {
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

template <class T>
Node<T> *SinglyLinkedList<T>::getNode(const int &index) const {
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
T SinglyLinkedList<T>::getData(const int &index) const {
    return getNode(index)->data;
}