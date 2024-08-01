#include "DoublyLinkedList.h"

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

    for (int i = 0; i < capacity; ++i) {
        this->deleteNodeHead();
    }

    // OR
    /*
    for (int i = 0; i < capacity; ++i) {
        this->deleteNodeTail();
    }
    */

    if (this->head != nullptr) {
        delete this->head;
        this->head = nullptr;
    }
    if (this->tail != nullptr) {
        delete this->tail;
        this->tail = nullptr;
    }
}

template <class T>
void DoublyLinkedList<T>::insertEmptyBetween(Node<T> *left, Node<T> *right, Node<T>* &newest) {
    assert(left != nullptr && right != nullptr);
    assert(left->next == right && right->prev == left);

    newest = new Node<T>();
    // join newest and right
    newest->next = right;
    right->prev = newest;
    // join newest and left
    newest->prev = left;
    left->next = newest;

    ++this->capacity;
}

template <class T>
void DoublyLinkedList<T>::insertBetween(Node<T> *left, Node<T> *right, const T &data) {
    Node<T> *newest = nullptr;
    this->insertEmptyBetween(left, right, newest);
    newest->data = data;

    ++this->size;
}

template <class T>
void DoublyLinkedList<T>::removeBetween(Node<T> *left, Node<T> *right) {
    assert(left != nullptr && right != nullptr);
    assert(left->next->next == right && right->prev->prev == left);

    // free memory
    delete left->next; 
    // join left and right
    left->next = right;
    right->prev = left;

    --this->size;
    --this->capacity;
}

template <class T>
void DoublyLinkedList<T>::addEmptyNodeHead(Node<T>* &newest) {
   
    newest = new Node<T>();

    // if list empty
    if (this->head == nullptr) {
        newest->next = this->head;
        newest->prev = nullptr;
        // actualize head
        this->head = newest;
    } 
    // not empty
    else {
        // join newest with head
        newest->next = this->head;
        this->head->prev = newest;
        newest->prev = nullptr;
        // actualize head
        this->head = newest;
    }

    ++this->capacity;
}

template <class T>
void DoublyLinkedList<T>::addNodeHead(const T &data) {
   
    Node<T> *newest = nullptr;
    this->addEmptyNodeHead(newest);
    newest->data = data;

    ++this->size;
}

template <class T>
void DoublyLinkedList<T>::addEmptyNodeTail(Node<T>* &newest) {

    newest = new Node<T>();
    
    // if list empty
    if (this->tail == nullptr) {
        newest->next = nullptr;
        newest->prev = this->tail;
        // actualize tail
        this->tail = newest;
    } 
    // not empty
    else {
        newest->next = nullptr;
        // join newest and tail
        newest->prev = this->tail;
        this->tail->next = newest;
        // actualize tail
        this->tail = newest;
    }

    ++this->capacity;
}

template <class T>
void DoublyLinkedList<T>::addNodeTail(const T &data) {
   
    Node<T> *newest = nullptr;
    addEmptyNodeTail(newest);
    newest->data = data;

    ++size;
}

template <class T>
void DoublyLinkedList<T>::deleteNodeTail() {
    // if list empty
    if (this->head == nullptr) return;

    // if list has 1 element
    if (this->head == this->tail) {
        delete this->head;
        this->head = this->tail = nullptr;
        return;
    }

    // actualize tail
    this->tail = this->tail->prev;
    // free memory
    delete this->tail->next;
    this->tail->next = nullptr;

    --this->capacity;
    --this->size;
}

template <class T>
void DoublyLinkedList<T>::deleteNodeHead() {
    // if list empty
    if (this->capacity == 0) return;

    // if list has 1 element
    if (this->capacity == 1) {
        delete this->head;
        this->head = this->tail = nullptr;
        return;
    }

    // actualize head
    this->head = this->head->next;
    // free memory
    delete this->head->prev;
    this->head->prev = nullptr;

    --this->capacity;
    --this->size;
}

template <class T>
void DoublyLinkedList<T>::insertNode(const int &index, const T &data) {
    // handle incorrect index, wont have to worry later
    assert(index >= 0 && index < capacity);

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;

    if (index == 0) this->addNodeHead(data); // this function checks if capacity is 0
    else if (index == this->capacity - 1) this->addNodeTail(data); // this function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on index and previous
        if (index < this->capacity/2) {
            current = this->head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            this->insertBetween(previous, current, data);

        } else {
            current = this->tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            this->insertBetween(current, previous, data); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = this->getNode(index);
        previous = current->prev; // previous = this->getNode(index - 1);
        this->insertBetween(previous, current, data);
        }
        */

        // OR
        /* 
        previous = this->getNode(index - 1);
        current = previous->next; // current = this->getNode(index);
        this->insertBetween(previous, current, data);
        }
        */
    }

    current = nullptr;
    previous = nullptr;
}

template <class T>
void DoublyLinkedList<T>::removeNode(const T &index) {
    // handle incorrect index, wont have to worry later
    assert(index >= 0 && index < this->capacity);

    Node<T> *current = nullptr;
    Node<T> *previous = nullptr;
    Node<T> *next = nullptr;

    if (index == 0) this->deleteNodeHead();    
    else if (index == this->capacity - 1) this->deleteNodeTail();
    else {
        // erase current node
        current = this->getNode(index);
        previous = current->prev; // previous = this->getNode(index - 1);
        this->removeBetween(previous, current->next);

        // OR
        // erase node between previous and next
        /*
        next = this->getNode(index + 1);
        previous = (current->prev)->prev; // previous = this->getNode(index - 1);
        this->removeBetween(previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        previous = this->getNode(index - 1);
        next = (previous->next)->next;// next = this->getNode(index + 1); 
        this->removeBetween(previous, next);
        */

       // OR
       // erase current node 
       /*
       if (index < this->capacity/2) {
            // find previous and next
            current = this->head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            // free memory
            delete current;
            previous->next = next;
            next->prev = previous;
            

        } else {
            // NOTE that here previous is on the right, next on the left, because of iterating backwards!
            current = this->tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            next = current->prev;
            // free memory
            delete current;
            // join next and previous (knowinh they are 'logically' swapped)
            next->next = previous;
            previous->prev = next;
        }   
        */
       
        // OR
        // erase current node but swap previous and next when iterating backward and use same formula
        if (index < this->capacity/2) {
            // find previous and next
            current = this->head;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            
        } else {
            // find previous and next
            current = this->tail;
            for (int i = 0; i < index; ++i) {
                previous = current;
                current = current->prev;
            }
            next = current->prev;
            // swap
            Node<T> *tmp = next;
            next = previous;
            previous = tmp;
        }          

        this->removeBetween(previous, next);
    }

    current = nullptr;
    previous = nullptr;
    next = nullptr;
}

template <class T>
void DoublyLinkedList<T>::removeNodeElement(const T &data) {

    Node<T> *current = this->head;
    Node<T> *previous = nullptr;

    while (current != nullptr) {
        
        if (current->data == data) {
            if (current == head) this->deleteNodeHead();
            else if (current == tail) this->deleteNodeTail();
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                delete current;

                // OR
                // erase current node
                this->removeBetween(previous, current->next);
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
void DoublyLinkedList<T>::print() const {
    // if list empty then dont dereference nullptrs!
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
int DoublyLinkedList<T>::getCapacity() const {
    return this->capacity;
}

template <class T>
int DoublyLinkedList<T>::getSize() const {
    return this->size;
}

template <class T>
Node<T> *DoublyLinkedList<T>::getHead() const {
    return this->head;
}

template <class T>
Node<T> *DoublyLinkedList<T>::getTail() const {
    return this->tail;
}

template <class T>
Node<T> *DoublyLinkedList<T>::getNode(const int &index) const {
    // handle incorrect index, wont have to worry later
    assert(index >= 0 && index < this->capacity);

    Node<T> *current = nullptr;

    if (index == 0) return this->getHead();
    else if (index == this->capacity - 1) return this->getTail();
    else {
        // check if its faster to iterate from the back or the front
        if (index < this->capacity/2) {
            // start from the head
            current = this->head;
            for (int i = 0; i < index; ++i) {
                // go forward
                current = current->next;
            }
        } else {
            // start from tail
            current = this->tail;
            for (int i = 0; i < index; ++i) {
                // go backward
                current = current->prev;
            }
        }
        return current;
    }
}

template <class T>
T DoublyLinkedList<T>::getData(const int &index) const {
    return this->getNode(index)->data;
}

template <class T>
void DoublyLinkedList<T>::setData(const int &index, const T &data) {
    this->getNode(index)->data = data;
}

template <class T>
void DoublyLinkedList<T>::assign(const T *array, const int &length) {
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
    /* for (i = 0; i < capacity; ++i) {
        this->setData(i, array[i]);
    } 
    */
    Node<T> *current = this->head;
    for (i = 0; i < this->capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}
