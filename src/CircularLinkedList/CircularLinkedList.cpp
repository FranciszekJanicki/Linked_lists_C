#include "CircularLinkedList.h"

template <class T>
CircularLinkedList<T>::CircularLinkedList() {

}

template <class T>
CircularLinkedList<T>::~CircularLinkedList() {

    for (int i = 0; i < capacity; ++i) {
        deleteNodeHead();
    }

    if (head != nullptr) delete head;
    if (tail != nullptr) delete tail;
}

template <class T>
void CircularLinkedList<T>::insertEmptyBetween(Node<T> *left, Node<T> *right, Node<T>* &newest) {

    newest = new Node<T>();
    newest->next = right;
    left->next = newest;

    ++capacity;
}

template <class T>
void CircularLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {

    Node<T> *newest = nullptr;

    if (left != right) {
        insertEmptyBetween(left, right, newest);
        newest->data = data;
        ++size;
    }
}

template <class T>
void CircularLinkedList<T>::removeBetween(Node<T> *left, Node<T> *right) {

    if (right != left && left->next != right) {
        // free memory
        delete left->next;
        // join left and right
        left->next = right;
        --size;
        --capacity;
    }
}

template <class T>
void CircularLinkedList<T>::addEmptyNodeHead(Node<T>* &newest) {

    newest = new Node<T>();

    // if list empty
    if (head == nullptr) {
        newest->next = head;
        // actualize head and tail
        head = tail = newest;
    }
    // not empty
    else {
        newest->next = head;
        // actualize head
        head = newest;
        tail->next = head;
    }

    ++capacity;
}

template <class T>
void CircularLinkedList<T>::addNodeHead(const T &data) {

    Node<T> *newest = nullptr;
    addEmptyNodeHead(newest);
    newest->data = data;
    
    ++size;
}

template <class T>
void CircularLinkedList<T>::addEmptyNodeTail(Node<T>* &newest) {

    newest = new Node<T>();

    // if list empty
    if (tail == nullptr) {        
        newest->next = head;
        // actualize head and tail
        head = tail = newest;
    } 
    // not empty
    else {
        newest->next = head;
        tail->next = newest;
        // actualize tail
        tail = newest;
    }

    ++capacity;
}

template <class T>
void CircularLinkedList<T>::addNodeTail(const T &data) {

    Node<T> *newest = nullptr;
    addEmptyNodeTail(newest);
    newest->data = data;

    ++size;
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
    for (int i = 0; i < capacity - 1; ++i) {
        current = current->next;
    }
    */
    // actualize tail
    tail = current;
    // free memory
    delete tail->next;
    tail->next = head;

    current = nullptr;
    --capacity;
    --size;
}

template <class T>
void CircularLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (capacity == 0) return;

    // if list has 1 element
    if (capacity == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    Node<T> *temp = head;
    // actualize head
    head = head->next;
    tail->next = head;
    // free memory
    delete temp;

    temp = nullptr;
    --capacity;
    --size;
}


template <class T>
void CircularLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > capacity) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) addNodeHead(data); 
    else if (index == capacity) addNodeTail(data);
    else {

        // just need to find second to last to index (because you can calculate current (index) by previous->next)
        // find previous index and index
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
void CircularLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    if (index < 0 || index > capacity) return;

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    if (index == 0) deleteNodeHead(); // this function checks if capacity is 0
    else if (index == capacity) deleteNodeTail(); // this function checks if capacity is 0
    else {
        // erase current node
        previous = getNode(index - 1);
        current = previous->next; // current = getNode(index);
        removeBetween(previous, current->next);

        // OR
        /*
        // erase node between previous and next (erase current node)
        previous = getNode(index - 1);
        next = (previous->next)->next;// next = current->next; // next = getNode(index + 1); 
        removeBetween(previous, current->next);
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
                // erase current node
                removeBetween(previous, current->next);
      
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
void CircularLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = head;
    Node<T> *previous = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == head) deleteNodeHead();
            else if (current == tail) deleteNodeTail();
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                // free memory
                delete current;
                --capacity;
                --size;

                // OR
                // erase current node
                removeBetween(previous, current->next);

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
        for (int i = 0; i < capacity; ++i) {
            printf(nullptr, current->data);
            current = current->next;
        }
        current = nullptr;
    }
}

template <class T>
int CircularLinkedList<T>::getCapacity() const {
    return capacity;
}

template <class T>
int CircularLinkedList<T>::getSize() const {
    return size;
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
    if (index < 0 || index > capacity) return nullptr;

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

template <class T>
void CircularLinkedList<T>::setData(const int &index, const T &data) {
    getNode(index)->data = data;
}

template <class T>
void CircularLinkedList<T>::assign(const T *array, const int &length) {
    if (array = nullptr || capacity == 0) return;

    // resize
    int sizeDifference = length - this->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node<T> *toAdd = nullptr;
            addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            deleteNodeTail();
        }
    }

    /* this has shitty complexity as every iteration will call getNode function, which iterates to the index*/
    /* for (i = 0; i < capacity; ++i) {
        setData(i, array[i]);
    } 
    */
    Node<T> *current = head;
    for (i = 0; i < capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}

