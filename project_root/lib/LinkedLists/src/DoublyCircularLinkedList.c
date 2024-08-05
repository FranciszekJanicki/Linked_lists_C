#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "DoublyCircularLinkedList.h"


void insertEmptyBetween(Node *left, Node *right, Node* &newest) {
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);

    newest = (Node *)malloc(sizeof(Node));
    // join newest and right
    newest->next = right;
    right->prev = newest;
    // join newest and left
    newest->prev = left;
    left->next = newest;

    ++handle->capacity;
}


void insertBetween(Node *left, Node *right, const T *pData) {
    Node *newest = NULL;
    handle->insertEmptyBetween(left, right, newest);
    newest->data = *pData;
    
    ++handle->size;
}


void removeBetween(Node *left, Node *right) {
    assert(left != NULL && right != NULL);
    assert(left->next->next == right && right->prev->prev == left);

    // free memory
    delete left->next; 
    // join left and right
    left->next = right;
    right->prev = left;

    --handle->size;
    --handle->capacity;
}


void addEmptyNodeHead(Node* &newest) {
   
    newest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        // join newest with head and tail and actualize
        newest->next = handle->head;
        newest->prev = handle->tail;
        handle->head = handle->tail = newest;
    } 
    // not empty
    else {
        // join newest and head
        newest->next = handle->head;
        handle->head->prev = newest;
        // join newest ant tail
        newest->prev = handle->tail;
        handle->tail->next = newest;
        // actualize head
        handle->head = newest;
    }

    ++handle->capacity;
}


void addNodeHead(const T *pData) {
   
    Node *newest = NULL;
    handle->addEmptyNodeHead(newest);
    newest->data = *pData;

    ++handle->size;
}


void addEmptyNodeTail(Node* &newest) {

    newest = (Node *)malloc(sizeof(Node));
    
    // if list empty
    if (handle->tail == NULL) {
        // join newest with head and tail and actualize
        newest->next = handle->head;
        newest->prev = handle->tail;
        handle->tail = handle->head = newest;
    } 
    // not empty
    else {
        // join newest and head
        newest->next = handle->head;
        handle->head->prev = newest;
        // join newest and tail
        newest->prev = handle->tail;
        handle->tail->next = newest;
        // actualize tail
        handle->tail = newest;  
    }

    ++handle->capacity;
}


void addNodeTail(const T *pData) {
   
    Node *newest = NULL;
    handle->addEmptyNodeTail(newest);
    newest->data = *pData;

    ++handle->size;
}

void deleteNodeTail(handle) {
    // if list empty
    if (handle->head == NULL) return;

    // if list has 1 element
    if (handle->head == handle->tail) {
        delete handle->head;
        handle->head = handle->tail = NULL;
        return;
    }

    // with doubly list you dont need to iterate to find second to last, because you have tail->prev
    // dont need to use temp, because you can use tail->next after changing tail addres to release deleted node
    // actualize tail
    handle->tail = handle->tail->prev;
    // free memory
    delete tail->next;
    // join head and tail
    handle->tail->next = handle->head;
    handle->head->prev = handle->tail;

    --handle->capacity;
    --handle->size;
}


void deleteNodeHead(handle) {
    // if list empty
    if (handle->capacity == 0) return;

    // if list has 1 element
    if (handle->capacity == 1) {
        delete head;
        handle->head = handle->tail = NULL;
        return;
    }

    // actualize head
    handle->head = handle->head->next;
    // free memory
    delete handle->head->prev;
    // join head and tail
    handle->head->prev = handle->tail;
    handle->tail->next = handle->head;

    --handle->capacity;
    --handle->size;
}


void insertNode(const int *pIndex, const T *pData) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) handle->addNodeHead(pData); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity - 1) handle->addNodeTail(pData); // handle function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on pIndex and previous
        if (*pIndex < handle->capacity/2) {
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            handle->insertBetween(previous, current, pData);

        } else {
            current = handle->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            handle->insertBetween(current, previous, pData); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = handle->getNode(*pIndex);
        previous = current->prev; // previous = handle->getNode(*pIndex - 1);
        handle->insertBetween(previous, current, pData);
        }
        */

        // OR
        /* 
        previous = handle->getNode(*pIndex - 1);
        current = previous->next; // current = handle->getNode(*pIndex);
        handle->insertBetween(previous, current, pData);
        }
        */
    }

    current = NULL;
    previous = NULL;
}


void removeNode(const T *pIndex) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) handle->deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) handle->deleteNodeTail(handle);
    else {
        // erase current node
        current = handle->getNode(*pIndex);
        previous = current->prev; // previous = handle->getNode(*pIndex - 1);
        handle->removeBetween(previous, current->next);

        // OR
        // erase node between previous and next
        /*
        next = handle->getNode(*pIndex + 1);
        previous = (current->prev)->prev; // previous = handle->getNode(*pIndex - 1);
        handle->removeBetween(previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        previous = handle->getNode(*pIndex - 1);
        next = (previous->next)->next;// next = handle->getNode(*pIndex + 1); 
        handle->removeBetween(previous, next);
        */

       // OR
       // erase current node 
       /*
       if (*pIndex < handle->capacity/2) {
            // find previous and next
            current = handle->head;
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
            current = handle->tail;
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
        // if (*pIndex < handle->capacity/2) {
        //     // find previous and next
        //     current = handle->head;
        //     for (int i = 0; i < *pIndex; ++i) {
        //         previous = current;
        //         current = current->next;
        //     }
        //     next = current->next;
            
        // } else {
        //     // find previous and next
        //     current = tail;
        //     for (int i = 0; i < *pIndex; ++i) {
        //         previous = current;
        //         current = current->prev;
        //     }
        //     next = current->prev;
        //     // swap
        //     Node *tmp = next;
        //     next = previous;
        //     previous = tmp;
        // }          

        // handle->removeBetween(previous, next);
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}


void removeNodeElement(const T *pData) {

    Node *current = handle->head;
    Node *previous = NULL;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) handle->deleteNodeHead(handle);
            else if (current == handle->tail) handle->deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                delete current;

                // OR
                // erase current node
                handle->removeBetween(previous, current->next);
            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void print(handle) {
    // if list empty then dont dereference NULLs!
    if (handle->head != NULL) {
        Node *current = handle->head;
        for (int i = 0; i < handle->capacity; ++i) {
            printf(NULL, current->data);
            current = current->next;
        }
    current = NULL;
    }
}


int getCapacity(handle) {
    return handle->capacity;
}


int getSize(handle) {
    return handle->size;
}


Node *getHead(handle) {
    return handle->head;
}


Node *getTail(handle) {
    return handle->tail;
}


Node *getNode(const int *pIndex) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return handle->getHead(handle);
    else if (*pIndex == handle->capacity - 1) return handle->getTail(handle);
    else {
        // check if its faster to iterate from the back or the front
        if (*pIndex < handle->capacity/2) {
            // start from the head
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                // go forward
                current = current->next;
            }
        } else {
            // start from tail
            current = handle->tail;
            for (int i = 0; i < *pIndex; ++i) {
                // go backward
                current = current->prev;
            }
        }
        return current;
    }
}


T getData(const int *pIndex) {
    return handle->getNode(*pIndex)->data;
}


void setData(const int *pIndex, const T *pData) {
    handle->getNode(*pIndex)->data = *pData;
}



void assign(const T *array, const int &length) {
    assert(array != NULL && length > 0);

    // resize
    int sizeDifference = length - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            handle->addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            handle->deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < capacity; ++i) {
        handle->setData(i, array[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}


#endif
