#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "DoublyLinkedList.h"




void insertEmptyBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, Node* &newest) {
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);

    newest = (Node *)malloc(sizeof(Node));
    // join newest and right
    newest->next = right;
    right->prev = newest;
    // join newest and left
    newest->prev = left;
    left->next = newest;

    ++this->capacity;
}


void insertBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, const T *pData) {
    Node *newest = NULL;
    this->insertEmptyBetween(left, right, newest);
    newest->data = *pData;

    ++this->size;
}


void removeBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right) {
    assert(left != NULL && right != NULL);
    assert(left->next->next == right && right->prev->prev == left);

    // free memory
    delete left->next; 
    // join left and right
    left->next = right;
    right->prev = left;

    --this->size;
    --this->capacity;
}


void addEmptyNodeHead(DoublyLinkedListHandle_t handle, Node* &newest) {
   
    newest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (this->head == NULL) {
        newest->next = this->head;
        newest->prev = NULL;
        // actualize head
        this->head = newest;
    } 
    // not empty
    else {
        // join newest with head
        newest->next = this->head;
        this->head->prev = newest;
        newest->prev = NULL;
        // actualize head
        this->head = newest;
    }

    ++this->capacity;
}


void addNodeHead(DoublyLinkedListHandle_t handle, const T *pData) {
   
    Node *newest = NULL;
    this->addEmptyNodeHead(newest);
    newest->data = *pData;

    ++this->size;
}


void addEmptyNodeTail(DoublyLinkedListHandle_t handle, Node* &newest) {

    newest = (Node *)malloc(sizeof(Node));
    
    // if list empty
    if (this->tail == NULL) {
        newest->next = NULL;
        newest->prev = this->tail;
        // actualize tail
        this->tail = newest;
    } 
    // not empty
    else {
        newest->next = NULL;
        // join newest and tail
        newest->prev = this->tail;
        this->tail->next = newest;
        // actualize tail
        this->tail = newest;
    }

    ++this->capacity;
}


void addNodeTail(DoublyLinkedListHandle_t handle, const T *pData) {
   
    Node *newest = NULL;
    addEmptyNodeTail(newest);
    newest->data = *pData;

    ++size;
}


void deleteNodeTail(DoublyLinkedListHandle_t handle) {
    // if list empty
    if (this->head == NULL) return;

    // if list has 1 element
    if (this->head == this->tail) {
        delete this->head;
        this->head = this->tail = NULL;
        return;
    }

    // actualize tail
    this->tail = this->tail->prev;
    // free memory
    delete this->tail->next;
    this->tail->next = NULL;

    --this->capacity;
    --this->size;
}


void deleteNodeHead(DoublyLinkedListHandle_t handle) {
    // if list empty
    if (this->capacity == 0) return;

    // if list has 1 element
    if (this->capacity == 1) {
        delete this->head;
        this->head = this->tail = NULL;
        return;
    }

    // actualize head
    this->head = this->head->next;
    // free memory
    delete this->head->prev;
    this->head->prev = NULL;

    --this->capacity;
    --this->size;
}


void insertNode(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) this->addNodeHead(pData); // this function checks if capacity is 0
    else if (*pIndex == this->capacity - 1) this->addNodeTail(pData); // this function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on pIndex and previous
        if (*pIndex < this->capacity/2) {
            current = this->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            this->insertBetween(previous, current, pData);

        } else {
            current = this->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            this->insertBetween(current, previous, pData); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = this->getNode(*pIndex);
        previous = current->prev; // previous = this->getNode(*pIndex - 1);
        this->insertBetween(previous, current, pData);
        }
        */

        // OR
        /* 
        previous = this->getNode(*pIndex - 1);
        current = previous->next; // current = this->getNode(*pIndex);
        this->insertBetween(previous, current, pData);
        }
        */
    }

    current = NULL;
    previous = NULL;
}


void removeNode(DoublyLinkedListHandle_t handle, const T *pIndex) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < this->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) this->deleteNodeHead(handle);    
    else if (*pIndex == this->capacity - 1) this->deleteNodeTail(handle);
    else {
        // erase current node
        current = this->getNode(*pIndex);
        previous = current->prev; // previous = this->getNode(*pIndex - 1);
        this->removeBetween(previous, current->next);

        // OR
        // erase node between previous and next
        /*
        next = this->getNode(*pIndex + 1);
        previous = (current->prev)->prev; // previous = this->getNode(*pIndex - 1);
        this->removeBetween(previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        previous = this->getNode(*pIndex - 1);
        next = (previous->next)->next;// next = this->getNode(*pIndex + 1); 
        this->removeBetween(previous, next);
        */

       // OR
       // erase current node 
       /*
       if (*pIndex < this->capacity/2) {
            // find previous and next
            current = this->head;
            for (int i = 0; i < *pIndex; ++i) {
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
            for (int i = 0; i < *pIndex; ++i) {
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
        if (*pIndex < this->capacity/2) {
            // find previous and next
            current = this->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            
        } else {
            // find previous and next
            current = this->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            next = current->prev;
            // swap
            Node *tmp = next;
            next = previous;
            previous = tmp;
        }          

        this->removeBetween(previous, next);
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}


void removeNodeElement(DoublyLinkedListHandle_t handle, const T *pData) {

    Node *current = this->head;
    Node *previous = NULL;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == head) this->deleteNodeHead(handle);
            else if (current == tail) this->deleteNodeTail(handle);
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
            // return; // dont stop iterating, remove all nodes with this pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void print(DoublyLinkedListHandle_t handle) const {
    // if list empty then dont dereference NULLs!
    if (this->head != NULL) {
        Node *current = this->head;
        for (int i = 0; i < this->capacity; ++i) {
            printf(NULL, current->data);
            current = current->next;
        }
    current = NULL;
    }
}


int getCapacity(DoublyLinkedListHandle_t handle) const {
    return this->capacity;
}


int getSize(handle) const {
    return this->size;
}


Node *getHead(DoublyLinkedListHandle_t handle) const {
    return this->head;
}


Node *getTail(DoublyLinkedListHandle_t handle) const {
    return this->tail;
}


Node *getNode(DoublyLinkedListHandle_t handle, const int *pIndex) const {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < this->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return this->getHead(handle);
    else if (*pIndex == this->capacity - 1) return this->getTail(handle);
    else {
        // check if its faster to iterate from the back or the front
        if (*pIndex < this->capacity/2) {
            // start from the head
            current = this->head;
            for (int i = 0; i < *pIndex; ++i) {
                // go forward
                current = current->next;
            }
        } else {
            // start from tail
            current = this->tail;
            for (int i = 0; i < *pIndex; ++i) {
                // go backward
                current = current->prev;
            }
        }
        return current;
    }
}


T getData(DoublyLinkedListHandle_t handle, const int *pIndex) const {
    return this->getNode(*pIndex)->data;
}


void setData(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    this->getNode(*pIndex)->data = *pData;
}


void assign(DoublyLinkedListHandle_t handle, const T *array, const int &length) {
    assert(array != NULL && length > 0);

    // resize
    int sizeDifference = length - this->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            this->addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            this->deleteNodeTail(handle);
        }
    }

    /* this has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < capacity; ++i) {
        this->setData(i, array[i]);
    } 
    */
    Node *current = this->head;
    for (i = 0; i < this->capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}

#endif
