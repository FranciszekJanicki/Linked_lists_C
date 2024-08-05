#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "CircularLinkedListHandle_t.h"
#include "node.h"

void insertEmptyBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, Node* *pNewest) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    *pNewest = (Node *)malloc(sizeof(Node));
    newest->next = right;
    left->next = *pNewest;

    ++capacity;
}


void insertBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    Node *newest = NULL;
    insertEmptyBetween(left, right, newest);
    newest->data = *pData;

    ++handle->size;
}


void removeBetween(CircularLinkedListHandle_t handle, Node *left, Node *right) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next->next == right);

    // free memory
    delete left->next;
    // join left and right
    left->next = right;

    --handle->size;
    --handle->capacity;
}


void addEmptyNodeHead(CircularLinkedListHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        *pNewest->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = *pNewest;
    }
    // not empty
    else {
        *pNewest->next = handle->head;
        // actualize head
        handle->head = *pNewest;
        handle->tail->next = handle->head;
    }

    ++handle->capacity;
}


void addNodeHead(CircularLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    addEmptyNodeHead(newest);
    newest->data = *pData;
    
    ++handle->size;
}


void addEmptyNodeTail(CircularLinkedListHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->tail == NULL) {        
        *pNewest->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = *pNewest;
    } 
    // not empty
    else {
        *pNewest->next = handle->head;
        handle->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;
    }

    ++handle->capacity;
}


void addNodeTail(CircularLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    addEmptyNodeTail(newest);
    newest->data = *pData;

    ++handle->size;
}


void deleteNodeTail(CircularLinkedListHandle_t handle) {
    assert(handle != NULL);

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
    assert(handle != NULL);

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
    assert(handle != NULL);
    assert(pIndex != NULL);
    assert(pData != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) addNodeHead(pData); 
    else if (*pIndex == handle->capacity) addNodeTail(pData);
    else {

        // just need to find second to last to pIndex (because you can calculate current (*pIndex) by previous->next)
        // find previous pIndex and pIndex
        previous = getNode(handle, *pIndex - 1);
        current = previous->next; // current = getNode(handle, *pIndex);
        insertBetween(previous, current, pData);

        // OR
        /*
        int i = 0;
        current = handle->head;
        previous = NULL;

        for (i; i < *pIndex; ++i) {
            previous = current;
            current = current->next;
        }
        insertBetween(previous, current, pData);
        */
    }
    // OR
    /* 
    int i = 0;
    current = handle->head;
    previous = NULL;

    while (current != NULL) {
        if (i == *pIndex) {
            if (current == handle->head) addNodeHead(pData);
            else if (current == handle->tail) addNodetail(pData);
            else {
                insertBetween(previous, current, pData);
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
    assert(handle != NULL);
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) deleteNodeHead(handle); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity) deleteNodeTail(handle); // handle function checks if capacity is 0
    else {
        // erase current node
        previous = getNode(handle, *pIndex - 1);
        current = previous->next; // current = getNode(handle, *pIndex);
        removeBetween(previous, current->next);

        // OR
        /*
        // erase node between previous and next (erase current node)
        previous = getNode(handle, *pIndex - 1);
        next = (previous->next)->next;// next = current->next; // next = getNode(handle, *pIndex + 1); 
        removeBetween(previous, current->next);
        */
    }

    // OR
    /*
    int i = 0;
    current = handle->head;
    while (current != NULL) {
        
        if (i == *pIndex) {
            if (current == handle->head) deleteNodeHead(handle);
            else if (current == handle->tail) deleteNodeTail(handle);
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

    previous = NULL;
    current = NULL;
}


void removeNodeElement(CircularLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *current = handle->head;
    Node *previous = NULL;
    int i = 0;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) deleteNodeHead(handle);
            else if (current == handle->tail) deleteNodeTail(handle);
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
                // removeBetween(previous, current->next);

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
    assert(handle != NULL);

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
    assert(handle != NULL);

    return handle->capacity;
}


int getSize(CircularLinkedListHandle_t handle) {
    assert(handle != NULL);

    return handle->size;
}


Node *getHead(CircularLinkedListHandle_t handle) {
    assert(handle != NULL);

    return handle->head;
}


Node *getTail(CircularLinkedListHandle_t handle) {
    assert(handle != NULL);

    return handle->tail;
}


Node *getNode(CircularLinkedListHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return getHead(handle);
    else if (*pIndex == handle->capacity - 1) return getTail(handle);
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
    assert(handle != NULL);
    assert(pIndex != NULL);

    return getNode(handle, *pIndex)->data;
}


void setData(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    assert(pData != NULL);

    getNode(handle, *pIndex)->data = *pData;
}


void assign(CircularLinkedListHandle_t handle, const T *array, const int *pLength) {
    assert(handle != NULL);
    assert(pLength != NULL);
    assert(array != NULL && length > 0);

    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            addEmptyNodeTail(toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            deleteNodeTail(handle);
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