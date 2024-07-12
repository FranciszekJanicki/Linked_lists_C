#include "DoublyCircularLinkedList.h"

template <class T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() {

}

template <class T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {

    for (int i = 0; i < length; ++i) {
        deleteNodeHead();
    }

    // OR
    /*
    for (int i = 0; i < length; ++i) {
        deleteNodeTail();
    }
    */

    if (head != nullptr) {
        delete head;
        head = nullptr;
    }
    if (tail != nullptr) {
        delete tail;
        tail = nullptr;
    }
}

template <class T>
/* be aware that this function takes node to the left and to the right of destination insertion,
so when iterating from the back and having current node to the left of node to be inserted and previous node to
the right of node to be inserted, then current goes as first parameter, previous as second parameter (opposing to iterating forward)
*/
void DoublyCircularLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {

    Node<T> *newest = nullptr;
    
    if (right != left) {
        newest = new Node<T>();
        newest->data = data;
        newest->next = right;
        left->next = newest;
        right->prev = newest;
    }

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addNodeHead(const T &data) {

    Node<T> *newest = new Node<T>();
    newest->data = data;
    newest->next = head;
    newest->prev = tail;

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::addNodeTail(const T &data) {

    Node<T> *newest = nullptr;

    // if list empty
    if (tail == nullptr) {
        newest = new Node<T>();
        newest->data = data;
        newest->next = head;
        newest->prev = tail;
        tail = newest;
    } 
    // not empty
    else {
        newest = new Node<T>();
        newest->data = data;
        newest->next = head;
        newest->prev = tail;
        tail->next = newest;
        tail = newest;
    }

    ++length;
}

template <class T>
void DoublyCircularLinkedList<T>::deleteNodeTail() {
    // if list empty
    if (head == nullptr) return;

    // if list has 1 element
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // with doubly list you dont need to iterate to find second to last, because you have tail->prev
    // dont need to use temp, because you can use tail->next after changing tail addres to release deleted node
    tail = tail->prev;
    delete tail->next;
    tail->next = head;

    --length;
}

template <class T>
void DoublyCircularLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (length == 0) return;

    // if list has 1 element
    if (length == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // dont need to use temp because deleted node is at head->prev (after changing head)
    head = head->next;
    delete head->prev;
    head->prev = tail;

    --length;
}

template <class T>
void DoublyCircularLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (length == 0 && index == 0) addNodeHead(data); 
    else if (length == index) addNodeTail(data);
    else {
        int i;

        // check if its faster to iterate from the front or the back, find pointers to node on index and previous
        if (index < length/2) {
            current = head;
            for (i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            insertBetween(previous, current, data);

        } else {
            current = tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            insertBetween(current, previous, data); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }
    }

    // OR
    /*
    int i;
    while (current != nullptr) {

        if (index < length/2) {
            i = 0;
            current = head;
            if (i == index) {

                if (current == head) addNodeHead(data);
                else if (current == tail) addNodeTail(data);
                else {
                    insertBetween(previous, current, data);
                }
                return;
            }

            previous = current;
            current = current->data;
            ++i;

        } else {
            i = length;
            current = tail;
            if (i == index) {

                if (current == head) addNodeHead(data);
                else if (current == tail) addNodeTail(data);
                else {
                    insertBetween(current, previous, data); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
                    // iterating backwards, the previous is on the right and current on the left !!!
                }
                return;
            }

            previous = current;
            current = current->prev;
            --i;
    }
    */   

    // OR
    /* 
    if (index < 0 || index > length) return;

    if (length == 0 && index == 0) addNodeHead(data); 
    else if (length == index) addNodeTail(data);
    else {
        current = getNode(index);
        previous = getNode(index - 1);
        insertBetween(previous, current, data);
    }
   */
}

template <class T>
void DoublyCircularLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return;

    // erase node between previous and current->next
    Node<T> *current = getNode(index);
    Node<T> *previous = getNode(index - 1);

    previous->next = current->next;
    (current->next)->prev = previous;
    delete current;

    // OR
    // erase node between current and previous
    /*
    current = getNode(index + 1);
    previous = getNode(index - 1);
    previous->next = current;
    delete current->prev;
    current->prev = previous;    
    */

    current = nullptr;
    previous = nullptr;

    --length;
}

template <class T>
void DoublyCircularLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = head;
    Node<T> *previous = nullptr;

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
void DoublyCircularLinkedList<T>::print() const {
    // if list empty then dont dereference nullptrs!
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
int DoublyCircularLinkedList<T>::getLength() const {
    return length;
}

template <class T>
T *DoublyCircularLinkedList<T>::getHead() const {
    return head;
}

template <class T>
T *DoublyCircularLinkedList<T>::getTail() const {
    return tail;
}

template <class T>
Node<T> *DoublyCircularLinkedList<T>::getNode(const int &index) const {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > length) return nullptr;

    Node<T> *current = nullptr;
    // check if its faster to iterate from the back or the front
    if (index < length/2) {
        // start from the head
        current = head;
        for (int i = 0; i < index; ++i) {
            // go forward
            current = current->next;
        }
    } else {
        // start from tail
        current = tail;
        for (int i = 0; i < index; ++i) {
            // go backward
            current = current->prev;
        }
    }

    return current;
}

template <class T>
T DoublyCircularLinkedList<T>::getData(const int &index) const {
    return getNode(index)->data;
}