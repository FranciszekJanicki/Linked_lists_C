#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "node.h"


/* return handle to dynamically allocated memory */
DoublyLinkedListHandle_t listCreateDynamically() {
    SinglyLinkedListHandle_t handle = (SinglyLinkedListHandle_t)malloc(sizeof(SinglyLinkedList));
    assert(handle != NULL);
    return handle;
}

/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyLinkedList listCreateStatically() {
    DoublyLinkedList list
    return list;
}

/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyLinkedListHandle_t listCreateStaticStatically() {
    static DoublyLinkedList list;
    DoublyLinkedListHandle_t handle = &list;
    return handle;
}

/* dynamically allocate memory and point passed handle at it */
void listCreateDynamicallyVoid(DoublyLinkedListHandle_t *pHandle) {
    // assert that passed ptr to handle isnt NULL
    assert(pHandle != NULL);

    // allocate memory and point handle at it
    *pHandle = (DoublyLinkedListHandle_t)malloc(sizeof(DoublyLinkedList));
    // check if allocation succeded
    assert(*pHandle != NULL);
}

/* statically allocate memory and copy it to memory under passed handle */
void listCreateStaticallyVoid(DoublyLinkedListHandle_t handle) {
    DoublyLinkedList list;
    *handle = list; // memcpy(handle, &list, sizeof(list)); // OK, COPYING STATICALLY ALLOCATED MEMORY
    // handle = &list; // WRONG!!! POINTING TO MEMORY THAT WILL GET DESTROYED AFTER THIS SCOPE RETURNS!!! APART FROM THAT 'handle' is a copy, to work on original handle would need *pHandle like above
}

/* if wanting to also free the handle pointer itself, would need to pass pointer to it, not just the copy */
void listDelete(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);
    // Node* current = handle->head;
    // for (int i = 0; i < handle->capacity; ++i) {
    //     free(current);
    //     current = current->next;
    // }
    for (int i = 0; i < handle->capacity; ++i) {
            deleteNodeHead(handle);
    }

    if (handle->head != NULL) free(handle->head);
    if (handle->tail != NULL) free(handle->tail);

    free(handle);
}

void insertEmptyBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, Node* *pNewest) {
    assert(handle != NULL);  
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);

    *pNewest = (Node *)malloc(sizeof(Node));
    // join newest and right
    *pNewest->next = right;
    right->prev = *pNewest;
    // join newest and left
    newest->prev = left;
    left->next = *pNewest;

    ++handle->capacity;
}


void insertBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(handle != NULL);  
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);
    assert(pData != NULL);

    Node *newest = NULL;
    insertEmptyBetween(handle, left, right, newest);
    newest->data = *pData;

    ++handle->size;
}


void removeBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right) {
    assert(handle != NULL);
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


void addEmptyNodeHead(DoublyLinkedListHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);  
    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        *pNewest->next = handle->head;
        *pNewest->prev = NULL;
        // actualize head
        handle->head = *pNewest;
    } 
    // not empty
    else {
        // join newest with head
        *pNewest->next = handle->head;
        handle->head->prev = *pNewest;
        *pNewest->prev = NULL;
        // actualize head
        handle->head = *pNewest;
    }

    ++handle->capacity;
}


void addNodeHead(DoublyLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL); 
    assert(pData != NULL);

    Node *newest = NULL;
    addEmptyNodeHead(handle, &newest);
    newest->data = *pData;

    ++handle->size;
}


void addEmptyNodeTail(DoublyLinkedListHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);  
    *pNewest = (Node *)malloc(sizeof(Node));
    
    // if list empty
    if (handle->tail == NULL) {
        *pNewest->next = NULL;
        *pNewest->prev = handle->tail;
        // actualize tail
        handle->tail = *pNewest;
    } 
    // not empty
    else {
        *pNewest->next = NULL;
        // join newest and tail
        *pNewest->prev = handle->tail;
        *pNewest->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;
    }

    ++handle->capacity;
}


void addNodeTail(DoublyLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL);  
    assert(pData != NULL);

    Node *newest = NULL;
    addEmptyNodeTail(handle, &newest);
    newest->data = *pData;

    ++size;
}


void deleteNodeTail(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    // if list empty
    if (handle->head == NULL) return;

    // if list has 1 element
    if (handle->head == handle->tail) {
        free(handle->head);
        handle->head = handle->tail = NULL;
        return;
    }

    // actualize tail
    handle->tail = handle->tail->prev;
    // free memory
    free(handle->tail->next);
    handle->tail->next = NULL;

    --handle->capacity;
    --handle->size;
}


void deleteNodeHead(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    // if list empty
    if (handle->capacity == 0) return;

    // if list has 1 element
    if (handle->capacity == 1) {
        free(handle->head);
        handle->head = handle->tail = NULL;
        return;
    }

    // actualize head
    handle->head = handle->head->next;
    // free memory
    free(handle->head->prev);
    handle->head->prev = NULL;

    --handle->capacity;
    --handle->size;
}


void insertNode(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    assert(pData != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) addNodeHead(handle, pData); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity - 1) addNodeTail(handle, pData); // handle function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on pIndex and previous
        if (*pIndex < handle->capacity/2) {
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            insertBetween(handle, previous, current, pData);

        } else {
            current = handle->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            insertBetween(handle, current, previous, pData); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = getNode(handle, *pIndex);
        prevIndex = *pIndex - 1;
        previous = current->prev; // previous = getNode(handle, prevIndex);
        insertBetween(handle, previous, current, pData);
        }
        */

        // OR
        /* 
        previous = getNode(handle, prevIndex);
        current = previous->next; // current = getNode(handle, &(*pIndex-1));
        insertBetween(handle, previous, current, pData);
        }
        */
    }

    current = NULL;
    previous = NULL;
}


void removeNode(DoublyLinkedListHandle_t handle, const T *pIndex) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) deleteNodeTail(handle);
    else {
        // erase current node
        current = getNode(handle, *pIndex);
        previous = current->prev; // previous = getNode(handle, &(*pIndex - 1));
        removeBetween(previous, current->next);

        // OR
        // erase node between previous and next
        /*
        next = getNode(handle, &(*pIndex + 1));
        previous = (current->prev)->prev; // previous = getNode(handle, &(*pIndex - 1));
        removeBetween(handle, previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        previous = getNode(handle, &(*pIndex - 1));
        next = (previous->next)->next;// next = getNode(handle, &(*pIndex + 1)); 
        removeBetween(handle, previous, next);
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
        if (*pIndex < handle->capacity/2) {
            // find previous and next
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            next = current->next;
            
        } else {
            // find previous and next
            current = handle->tail;
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

        removeBetween(handle, previous, next);
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}


void removeNodeElement(DoublyLinkedListHandle_t handle, const T *pData) {
    assert(handle != NULL);  
    assert(pData != NULL);

    Node *current = handle->head;
    Node *previous = NULL;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) deleteNodeHead(handle);
            else if (current == handle->tail) deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                free(current);

                // OR
                // erase current node
                removeBetween(handle, previous, current->next);
            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void print(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

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


int getCapacity(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    return handle->capacity;
}


int getSize(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    return handle->size;
}


Node *getHead(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    return handle->head;
}


Node *getTail(DoublyLinkedListHandle_t handle) {
    assert(handle != NULL);  

    return handle->tail;
}


Node *getNode(DoublyLinkedListHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);    
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return getHead(handle);
    else if (*pIndex == handle->capacity - 1) return getTail(handle);
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


T getData(DoublyLinkedListHandle_t handle, const int *pIndex) {  
    assert(handle != NULL);  
    assert(pIndex != NULL);

    return getNode(handle, *pIndex)->data;
}


void setData(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData) {  
    assert(handle != NULL);  
    assert(pIndex != NULL);
    assert(pData != NULL);

    getNode(handle, *pIndex)->data = *pData;
}


void assign(DoublyLinkedListHandle_t handle, const T *array, const int *pLength) {
    assert(pLength != NULL);    
    assert(handle != NULL);
    assert(array != NULL && length > 0);

    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            addEmptyNodeTail(handle, &toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < capacity; ++i) {
        handle->setData(handle, &i, &array[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = array[i];
        current = current->next;
    }
}