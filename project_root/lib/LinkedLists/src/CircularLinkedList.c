#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "CircularLinkedListHandle_t.h"


void insertEmptyBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, Node* &newest) {
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    newest = (Node *)malloc(sizeof(Node));
    newest->next = right;
    left->next = newest;

    ++capacity;
}


void insertBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, const T *pData) {
    Node *newest = NULL;
    handle->insertEmptyBetween(left, right, newest);
    newest->data = *pData;

    ++handle->size;
}


void removeBetween(CircularLinkedListHandle_t handle, Node *left, Node *right) {
    assert(left != NULL && right != NULL);
    assert(left->next->next == right);

    // free memory
    delete left->next;
    // join left and right
    left->next = right;

    --handle->size;
    --handle->capacity;
}


void addEmptyNodeHead(CircularLinkedListHandle_t handle, Node* &newest) {

    newest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        newest->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = newest;
    }
    // not empty
    else {
        newest->next = handle->head;
        // actualize head
        handle->head = newest;
        handle->tail->next = handle->head;
    }

    ++handle->capacity;
}


void addNodeHead(CircularLinkedListHandle_t handle, const T *pData) {

    Node *newest = NULL;
    handle->addEmptyNodeHead(newest);
    newest->data = *pData;
    
    ++handle->size;
}


void addEmptyNodeTail(CircularLinkedListHandle_t handle, Node* &newest) {

    newest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->tail == NULL) {        
        newest->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = newest;
    } 
    // not empty
    else {
        newest->next = handle->head;
        handle->tail->next = newest;
        // actualize tail
        handle->tail = newest;
    }

    ++handle->capacity;
}


void addNodeTail(CircularLinkedListHandle_t handle, const T *pData) {

    Node *newest = NULL;
    handle->addEmptyNodeTail(newest);
    newest->data = *pData;

    ++handle->size;
}


void deleteNodeTail(CircularLinkedListHandle_t handle) {
    // if list empty
    if (handle->head == NULL) return;

    // if list has 1 element
    if (handle->head == handle->tail) {
        delete handle->head;
        handle->head = handle->tail = NULL;
        return;
    }

    // find second to last 
    Node *current = handle->head;
    while (current->next != handle->tail) {
        current = current->next;
    }
    // OR
    /*
    // find second to last 
    Node *current = handle->head;
    for (int i = 0; i < handle->capacity - 1; ++i) {
        current = current->next;
    }
    */
    // actualize tail
    handle->tail = current;
    // free memory
    delete handle->tail->next;
    handle->tail->next = handle->head;

    current = NULL;
    --handle->capacity;
    --handle->size;
}


void deleteNodeHead(CircularLinkedListHandle_t handle) {
    // if list empty
    if (handle->capacity == 0) return;

    // if list has 1 element
    if (handle->capacity == 1) {
        delete handle->head;
        handle->head = handle->tail = NULL;
        return;
    }

    Node *temp = handle->head;
    // actualize head
    handle->head = handle->head->next;
    handle->tail->next = handle->head;
    // free memory
    delete temp;

    temp = NULL;
    --handle->capacity;
    --handle->size;
}



void insertNode(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) handle->addNodeHead(pData); 
    else if (*pIndex == handle->capacity) handle->addNodeTail(pData);
    else {

        // just need to find second to last to pIndex (because you can calculate current (*pIndex) by previous->next)
        // find previous pIndex and pIndex
        previous = handle->getNode(*pIndex - 1);
        current = previous->next; // current = handle->getNode(*pIndex);
        handle->insertBetween(previous, current, pData);

        // OR
        /*
        int i = 0;
        current = handle->head;
        previous = NULL;

        for (i; i < *pIndex; ++i) {
            previous = current;
            current = current->next;
        }
        handle->insertBetween(previous, current, pData);
        */
    }
    // OR
    /* 
    int i = 0;
    current = handle->head;
    previous = NULL;

    while (current != NULL) {
        if (i == *pIndex) {
            if (current == handle->head) handle->addNodeHead(pData);
            else if (current == handle->tail) handle->addNodetail(pData);
            else {
                handle->insertBetween(previous, current, pData);
            }
            return; // stop iterating
        }
        previous = current;
        current = current->next;
        ++i;
    }
    */  

   previous = NULL;
   current = NULL;
}


void removeNode(CircularLinkedListHandle_t handle, const T *pIndex) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) handle->deleteNodeHead(handle); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity) handle->deleteNodeTail(handle); // handle function checks if capacity is 0
    else {
        // erase current node
        previous = handle->getNode(*pIndex - 1);
        current = previous->next; // current = handle->getNode(*pIndex);
        handle->removeBetween(previous, current->next);

        // OR
        /*
        // erase node between previous and next (erase current node)
        previous = handle->getNode(*pIndex - 1);
        next = (previous->next)->next;// next = current->next; // next = handle->getNode(*pIndex + 1); 
        handle->removeBetween(previous, current->next);
        */
    }

    // OR
    /*
    int i = 0;
    current = handle->head;
    while (current != NULL) {
        
        if (i == *pIndex) {
            if (current == handle->head) handle->deleteNodeHead(handle);
            else if (current == handle->tail) handle->deleteNodeTail(handle);
            else {
                // erase current node
                handle->removeBetween(previous, current->next);
      
            }
            return; // stop iterating
        }

        previous = current;
        current = current->next;
        ++i; 
    }
    */

    previous = NULL;
    current = NULL;
}


void removeNodeElement(CircularLinkedListHandle_t handle, const T *pData) {

    Node *current = handle->head;
    Node *previous = NULL;
    int i = 0;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) handle->deleteNodeHead(handle);
            else if (current == handle->tail) handle->deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                // free memory
                delete current;
                --handle->capacity;
                --handle->size;

                // OR
                // erase current node
                // handle->removeBetween(previous, current->next);

            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void print(CircularLinkedListHandle_t handle) {
    // if list empty, avoid dereferencing NULL
    if (handle->head != NULL) {
        Node *current = handle->head;
        for (int i = 0; i < handle->capacity; ++i) {
            printf(NULL, current->data);
            current = current->next;
        }
        current = NULL;
    }
}


int getCapacity(CircularLinkedListHandle_t handle) {
    return handle->capacity;
}


int getSize(CircularLinkedListHandle_t handle) {
    return handle->size;
}


Node *getHead(CircularLinkedListHandle_t handle) {
    return handle->head;
}


Node *getTail(CircularLinkedListHandle_t handle) {
    return handle->tail;
}


Node *getNode(CircularLinkedListHandle_t handle, const int *pIndex) {
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return handle->getHead(handle);
    else if (*pIndex == handle->capacity - 1) return handle->getTail(handle);
    else {
        current = handle->head;
        int i = 0;

        while (i < *pIndex) {
            current = current->next;
            ++i;
        }
        return current;
    }
}


T getData(CircularLinkedListHandle_t handle, const int *pIndex) {
    return handle->getNode(*pIndex)->data;
}


void setData(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    handle->getNode(*pIndex)->data = *pData;
}


void assign(CircularLinkedListHandle_t handle, const T *array, const int &length) {
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
