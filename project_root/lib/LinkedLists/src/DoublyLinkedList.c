#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "node.h"


/* return handle to dynamically allocated memory */
DoublyLinkedHandle_t dl_listCreateDynamically() {
    DoublyLinkedHandle_t handle = (DoublyLinkedHandle_t)malloc(sizeof(DoublyLinkedList));
    assert(handle != NULL);
    return handle;
}

/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyLinkedList dl_listCreateStatically() {
    DoublyLinkedList list;
    return list;
}

/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyLinkedHandle_t dl_listCreateStaticStatically() {
    static DoublyLinkedList list;
    DoublyLinkedHandle_t handle = &list;
    return handle;
}

/* dynamically allocate memory and point passed handle at it */
void dl_listCreateDynamicallyVoid(DoublyLinkedHandle_t *pHandle) {
    // assert that passed ptr to handle isnt NULL
    assert(pHandle != NULL);

    // allocate memory and point handle at it
    *pHandle = (DoublyLinkedHandle_t)malloc(sizeof(DoublyLinkedList));
    // check if allocation succeded
    assert(*pHandle != NULL);
}

/* statically allocate memory and copy it to memory under passed handle */
void dl_listCreateStaticallyVoid(DoublyLinkedHandle_t handle) {
    DoublyLinkedList list;
    *handle = list; // memcpy(handle, &list, sizeof(list)); // OK, COPYING STATICALLY ALLOCATED MEMORY
    // handle = &list; // WRONG!!! POINTING TO MEMORY THAT WILL GET DESTROYED AFTER THIS SCOPE RETURNS!!! APART FROM THAT 'handle' is a copy, to work on original handle would need *pHandle like above
}

/* if wanting to also free the handle pointer itself, would need to pass pointer to it, not just the copy */
void dl_listDelete(DoublyLinkedHandle_t handle) {
    assert(handle != NULL);
    // Node* current = handle->head;
    // for (int i = 0; i < handle->capacity; ++i) {
    //     free(current);
    //     current = current->next;
    // }
    for (int i = 0; i < handle->capacity; ++i) {
            dl_deleteNodeHead(handle);
    }

    if (handle->head != NULL) free(handle->head);
    if (handle->tail != NULL) free(handle->tail);

    free(handle);
}

void dl_insertEmptyBetween(DoublyLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest) {
    assert(handle != NULL);  
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);

    *pNewest = (Node *)malloc(sizeof(Node));
    // join newest and right
    (*pNewest)->next = right;
    right->prev = *pNewest;
    // join newest and left
    (*pNewest)->prev = left;
    left->next = *pNewest;

    ++handle->capacity;
}


void dl_insertBetween(DoublyLinkedHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(handle != NULL);  
    assert(left != NULL && right != NULL);
    assert(left->next == right && right->prev == left);
    assert(pData != NULL);

    Node *newest = NULL;
    dl_insertEmptyBetween(handle, left, right, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void dl_removeBetween(DoublyLinkedHandle_t handle, Node *left, Node *right) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next->next == right && right->prev->prev == left);

    // free memory
    free(left->next); 
    // join left and right
    left->next = right;
    right->prev = left;

    --handle->size;
    --handle->capacity;
}


void dl_addEmptyNodeHead(DoublyLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);  
    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        (*pNewest)->next = handle->head;
        (*pNewest)->prev = NULL;
        // actualize head
        handle->head = *pNewest;
    } 
    // not empty
    else {
        // join newest with head
        (*pNewest)->next = handle->head;
        handle->head->prev = *pNewest;
        (*pNewest)->prev = NULL;
        // actualize head
        handle->head = *pNewest;
    }

    ++handle->capacity;
}


void dl_addNodeHead(DoublyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL); 
    assert(pData != NULL);

    Node *newest = NULL;
    dl_addEmptyNodeHead(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void dl_addEmptyNodeTail(DoublyLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);  
    *pNewest = (Node *)malloc(sizeof(Node));
    
    // if list empty
    if (handle->tail == NULL) {
        (*pNewest)->next = NULL;
        (*pNewest)->prev = handle->tail;
        // actualize tail
        handle->tail = *pNewest;
    } 
    // not empty
    else {
        (*pNewest)->next = NULL;
        // join newest and tail
        (*pNewest)->prev = handle->tail;
        handle->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;
    }

    ++handle->capacity;
}


void dl_addNodeTail(DoublyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);  
    assert(pData != NULL);

    Node *newest = NULL;
    dl_addEmptyNodeTail(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void dl_deleteNodeTail(DoublyLinkedHandle_t handle) {
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


void dl_deleteNodeHead(DoublyLinkedHandle_t handle) {
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


void dl_insertNode(DoublyLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    assert(pData != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) dl_addNodeHead(handle, pData); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity - 1) dl_addNodeTail(handle, pData); // handle function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on pIndex and previous
        if (*pIndex < handle->capacity/2) {
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            dl_insertBetween(handle, previous, current, pData);

        } else {
            current = handle->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            dl_insertBetween(handle, current, previous, pData); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = dl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = dl_getNode(handle, &prev_index);
        dl_insertBetween(handle, previous, current, pData);
        }
        */

        // OR
        /* 
        int prev_index = *pIndex - 1;
        previous = dl_getNode(handle, &prev_index);
        int current_index = *pIndex;
        current = previous->next; // current = dl_getNode(handle, &current_index);
        dl_insertBetween(handle, previous, current, pData);
        }
        */
    }

    current = NULL;
    previous = NULL;
}


void dl_removeNode(DoublyLinkedHandle_t handle, const T *pIndex) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) dl_deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) dl_deleteNodeTail(handle);
    else {
        // erase current node
        current = dl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = dl_getNode(handle, &prev_index);
        dl_removeBetween(handle, previous, current->next);

        // OR
        // erase node between previous and next
        /*
        int next_index = *pIndex + 1;
        next = dl_getNode(handle, &next_index);
        int prev_index = *pIndex - 1;
        previous = (next->prev)->prev; // previous = dl_getNode(handle, &prev_index);
        dl_removeBetween(handle, previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        int prev_index = *pIndex - 1;
        previous = dl_getNode(handle, &prev_index);
        int next_index = *pIndex + 1;
        next = (previous->next)->next;// next = dl_getNode(handle, &next_index); 
        dl_removeBetween(handle, previous, next);
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
            free(current;
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
            free(current;
            // join next and previous (knowinh they are 'logically' swapped)
            next->next = previous;
            previous->prev = next;
        }   
        */
       
        // OR
        // erase current node but swap previous and next when iterating backward and use same formula
        /*
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

        dl_removeBetween(handle, previous, next);
        */
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}


void dl_removeNodeElement(DoublyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);  
    assert(pData != NULL);

    Node *current = handle->head;
    Node *previous = NULL;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) dl_deleteNodeHead(handle);
            else if (current == handle->tail) dl_deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                free(current);

                // OR
                // erase current node
                dl_removeBetween(handle, previous, current->next);
            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void dl_print(DoublyLinkedHandle_t handle) {
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


int dl_getCapacity(DoublyLinkedHandle_t handle) {
    assert(handle != NULL);  

    return handle->capacity;
}


int dl_getSize(DoublyLinkedHandle_t handle) {
    assert(handle != NULL);  

    return handle->size;
}


Node *dl_getHead(DoublyLinkedHandle_t handle) {
    assert(handle != NULL);  

    return handle->head;
}


Node *dl_getTail(DoublyLinkedHandle_t handle) {
    assert(handle != NULL);  

    return handle->tail;
}


Node *dl_getNode(DoublyLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);    
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return dl_getHead(handle);
    else if (*pIndex == handle->capacity - 1) return dl_getTail(handle);
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


T dl_getData(DoublyLinkedHandle_t handle, const int *pIndex) {  
    assert(handle != NULL);  
    assert(pIndex != NULL);

    return dl_getNode(handle, pIndex)->data;
}


void setData(DoublyLinkedHandle_t handle, const int *pIndex, const T *pData) {  
    assert(handle != NULL);  
    assert(pIndex != NULL);
    assert(pData != NULL);

    dl_getNode(handle, pIndex)->data = *pData;
}


void dl_assign(DoublyLinkedHandle_t handle, const T *pArray, const int *pLength) {
    assert(handle != NULL);
    assert(pLength != NULL);
    assert(pArray!= NULL && *pLength > 0);
    
    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            dl_addEmptyNodeTail(handle, &toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            dl_deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < handle->capacity; ++i) {
        handle->dl_setData(handle, &i, &pArray[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = pArray[i];
        current = current->next;
    }
}