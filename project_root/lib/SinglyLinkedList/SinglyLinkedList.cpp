#include "SinglyLinkedList.h"

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {

}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {

    for (int i = 0; i < capacity; ++i) {
        this->deleteNodeHead();
    }

    if (this->head != nullptr) delete this->head;
    if (this->tail != nullptr) delete this->tail;
}

template <class T>
void SinglyLinkedList<T>::insertEmptyBetween(Node<T> *left, Node<T> *right, Node<T>* &newest) {
    assert(left != nullptr && right != nullptr);
    assert(left->next == right);

    newest = new Node<T>();
    newest->next = right;
    left->next = newest;

    ++this->capacity;
}

template <class T>
void SinglyLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {
    Node<T> *newest = nullptr;
    this->insertEmptyBetween(left, right, newest);
    newest->data = data;

    ++this->size;
}

template <class T>
void SinglyLinkedList<T>::removeBetween(Node<T> *left, Node<T> *right) {
    assert(left != nullptr && right != nullptr);
    assert(left->next->next == right);

    // free memory
    delete left->next;
    // join left and right
    left->next = right;
    
    --this->size;
    --this->capacity;
}

template <class T>
void SinglyLinkedList<T>::addEmptyNodeHead(Node<T>* &newest) {
    // in single list dont have to check if list is empty or not for head insertion
    newest = new Node<T>();
    newest->next = this->head;
    // actualize head
    this->head = newest;

    ++this->capacity;
}

template <class T>
void SinglyLinkedList<T>::addNodeHead(const T &data) {

    Node<T> *newest = nullptr;
    this->addEmptyNodeHead(newest);
    newest->data = data;
    
    ++this->size;
}

template <class T>
void SinglyLinkedList<T>::addEmptyNodeTail(Node<T>* &newest) {
    newest = new Node<T>();

    // if list empty
    if (this->tail == nullptr) {        
        newest->next = nullptr;
        // actualize tail
        this->tail = newest;
    } 
    // not empty
    else {
        newest->next = nullptr;
        this->tail->next = newest;
        // actualize tail
        this->tail = newest;
    }

    ++this->capacity;
}

template <class T>
void SinglyLinkedList<T>::addNodeTail(const T &data) {
    Node<T> *newest = nullptr;
    this->addEmptyNodeTail(newest);
    newest->data = data;

    ++this->size;
}

template <class T>
void SinglyLinkedList<T>::deleteNodeTail() {
    // if list empty
    if (this->head == nullptr) return;

    // if list has 1 element
    if (this->head == this->tail) {
        delete this->head;
        this->head = this->tail = nullptr;
        return;
    }

    // find second to last 
    Node<T> *current = this->head;
    while (current->next != this->tail) {
        current = current->next;
    }
    // OR
    /*
    // if list empty
    if (capacity == 0) return;

    // if list has 1 element
    if (capacity == 1) {
        delete head;
        head = tail = nullptr;
        return;
    }

    // find second to last 
    Node<T> *current = head;
    for (int i = 0; i < capacity - 1; ++i) {
        current = current->next;
    }
    */
    // actualize tail
    this->tail = current;
    // free memory
    delete this->tail->next;
    // actualize tail edge
    this->tail->next = nullptr;

    current = nullptr;

    --this->capacity;
    --this->size;
}

template <class T>
void SinglyLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (this->capacity == 0) return;

    // if list has 1 element
    if (this->capacity == 1) {
        delete this->head;
        this->head = this->tail = nullptr;
        return;
    }

    Node<T> *temp = this->head;
    // actualize head
    this->head = this->head->next;
    // free memory
    delete temp;
    temp = nullptr;

    --this->capacity;
    --this->size;
}

template <class T>
void SinglyLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    assert(index >= 0 && index < this->capacity);

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) this->addNodeHead(data); 
    else if (index == this->capacity) this->addNodeTail(data);
    else {

        // just need to find second to last to index (because you can calculate current (index) by previous->next)
        // find previous index and index
        previous = this->getNode(index - 1);
        current = previous->next; // current = this->getNode(index);
        this->insertBetween(previous, current, data);

        // OR
        /*
        int i = 0;
        current = this->head;
        previous = nullptr;

        for (i; i < index; ++i) {
            previous = current;
            current = current->next;
        }
        this->insertBetween(previous, current, data);
        */
    }
    // OR
    /* 
    int i = 0;
    current = head;
    previous = nullptr;

    while (current != nullptr) {
        if (i == index) {
            if (current == this->head) this->addNodeHead(data);
            else if (current == this->tail) this->addNodetail(data);
            else {
                this->insertBetween(previous, current, data);
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
    assert(index >= 0 && index < this->capacity);

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    if (index == 0) this->deleteNodeHead(); // this function checks if capacity is 0
    else if (index == this->capacity - 1) this->deleteNodeTail(); // this function checks if capacity is 0
    else {
        // erase current node
        previous = this->getNode(index - 1);
        current = previous->next; // current = this->getNode(index);
        this->removeBetween(previous, current->next);

        // OR
        /*
        // erase node between previous and next (erase current node)
        previous = this->getNode(index - 1);
        next = (previous->next)->next;// next = current->next; // next = this->getNode(index + 1); 
        this->removeBetween(previous, current->next);
        */
    }

    // OR
    /*
    int i = 0;
    current = this->head;
    while (current != nullptr) {
        
        if (i == index) {
            if (current == this->head) this->deleteNodeHead();
            else if (current == this->tail) this->deleteNodeTail();
            else {
                // erase current node
                this->removeBetween(previous, current->next);
      
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

    Node<T> *current = this->head;
    Node<T> *previous = nullptr;
    int i = 0;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == this->head) this->deleteNodeHead();
            else if (current == this->tail) this->deleteNodeTail();
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                // free memory
                delete current;
                --this->capacity;
                --this->size;

                // OR
                // erase current node
                // this->removeBetween(previous, current->next);

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
    if (this->head != nullptr) {
        Node<T> *current = this->head;
        for (int i = 0; i < this->capacity; ++i) {
            printf(nullptr, current->data);
            current = current->next;
        }
        current = nullptr;
    }
}

template <class T>
int SinglyLinkedList<T>::getCapacity() const {
    return this->capacity;
}

template <class T>
int SinglyLinkedList<T>::getSize() const {
    return this->size;
}

template <class T>
Node<T> *SinglyLinkedList<T>::getHead() const {
    return const_cast<Node<T> *>(this->head);
}

template <class T>
Node<T> *SinglyLinkedList<T>::getTail() const {
    return const_cast<Node<T> *>(this->tail);
}

template <class T>
Node<T> *SinglyLinkedList<T>::getNode(const int &index) const {
    // handle incorrect index, wont have to worry later
    assert(index >= 0 && index < this->capacity);

    Node<T> *current = nullptr;

    if (index == 0) return this->getHead();
    else if (index == this->capacity - 1) return this->getTail();
    else {
        current = this->head;
        int i = 0;

        while (i < index) {
            current = current->next;
            ++i;
        }
        return const_cast<Node<T> *>(current);
    }
}

template <class T>
T SinglyLinkedList<T>::getData(const int &index) const {
    return this->getNode(index)->data;
}

template <class T>
void  SinglyLinkedList<T>::setData(const int &index, const T &data) {
    this->getNode(index)->data = data;
}

template <class T>
void SinglyLinkedList<T>::assign(const T *array, const int &length) {
    assert(array != nullptr && length > 0);

    // resize
    int sizeDifference = length - this->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node<T> *toAdd = nullptr;
            this->addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            this->deleteNodeTail();
        }
    }

    /* this has shitty complexity as every iteration will call getNode function, which iterates to the index*/
    /* for (i = 0; i < this->capacity; ++i) {
        this->setData(i, array[i]);
    } 
    */
    Node<T> *current = this->head;
    for (i = 0; i < this->capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}