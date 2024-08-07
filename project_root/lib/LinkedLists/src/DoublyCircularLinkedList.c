#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "DoublyCircularLinkedList.h"
#include "node.h"


/* return handle to dynamically allocated memory */
DoublyCircLinkedHandle_t dcl_listCreateDynamically() {
    DoublyCircLinkedHandle_t handle = (DoublyCircLinkedHandle_t)malloc(sizeof(DoublyCircularLinkedList));
    assert(handle != NULL);
    return handle;
}

/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyCircularLinkedList dcl_listCreateStatically() {
    DoublyCircularLinkedList list;
    return list;
}

/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyCircLinkedHandle_t dcl_listCreateStaticStatically() {
    static DoublyCircularLinkedList list;
    DoublyCircLinkedHandle_t handle = &list;
    return handle;
}

/* dynamically allocate memory and point passed handle at it */
void dcl_listCreateDynamicallyVoid(DoublyCircLinkedHandle_t *pHandle) {
    // assert that passed ptr to handle isnt NULL
    assert(pHandle != NULL);

    // allocate memory and point handle at it
    *pHandle = (DoublyCircLinkedHandle_t)malloc(sizeof(DoublyCircularLinkedList));
    // check if allocation succeded
    assert(*pHandle != NULL);
}

/* statically allocate memory and copy it to memory under passed handle */
void dcl_listCreateStaticallyVoid(DoublyCircLinkedHandle_t handle) {
    DoublyCircularLinkedList list;
    *handle = list; // memcpy(handle, &list, sizeof(list)); // OK, COPYING STATICALLY ALLOCATED MEMORY
    // handle = &list; // WRONG!!! POINTING TO MEMORY THAT WILL GET DESTROYED AFTER THIS SCOPE RETURNS!!! APART FROM THAT 'handle' is a copy, to work on original handle would need *pHandle like above
}

/* if wanting to also free the handle pointer itself, would need to pass pointer to it, not just the copy */
void dcl_listDelete(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);
    // Node* current = handle->head;
    // for (int i = 0; i < handle->capacity; ++i) {
    //     free(current);
    //     current = current->next;
    // }
    for (int i = 0; i < handle->capacity; ++i) {
            dcl_deleteNodeHead(handle);
    }

    if (handle->head != NULL) free(handle->head);
    if (handle->tail != NULL) free(handle->tail);

    free(handle);
}

void dcl_insertEmptyBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest) {
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


void dcl_insertBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next->next == right && right->prev->prev == left);
    assert(pData != NULL);

    Node *newest = NULL;
    dcl_insertEmptyBetween(handle, left, right, &newest);
    assert(newest != NULL); 
    newest->data = *pData;
    
    ++handle->size;
}


void dcl_removeBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right) {
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


void dcl_addEmptyNodeHead(DoublyCircLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        // join newest with head and tail and actualize
        (*pNewest)->next = handle->head;
        (*pNewest)->prev = handle->tail;
        handle->head = handle->tail = *pNewest;
    } 
    // not empty
    else {
        // join newest and head
        (*pNewest)->next = handle->head;
        handle->head->prev = *pNewest;
        // join newest ant tail
        (*pNewest)->prev = handle->tail;
        handle->tail->next = *pNewest;
        // actualize head
        handle->head = *pNewest;
    }

    ++handle->capacity;
}


void dcl_addNodeHead(DoublyCircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);   
    assert(pData != NULL);

    Node *newest = NULL;
    dcl_addEmptyNodeHead(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void dcl_addEmptyNodeTail(DoublyCircLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));
    
    // if list empty
    if (handle->tail == NULL) {
        // join newest with head and tail and actualize
        (*pNewest)->next = handle->head;
        (*pNewest)->prev = handle->tail;
        handle->tail = handle->head = *pNewest;
    } 
    // not empty
    else {
        // join newest and head
        (*pNewest)->next = handle->head;
        handle->head->prev = *pNewest;
        // join newest and tail
        (*pNewest)->prev = handle->tail;
        handle->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;  
    }

    ++handle->capacity;
}


void dcl_addNodeTail(DoublyCircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);
   
    Node *newest = NULL;
    dcl_addEmptyNodeTail(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}

void dcl_deleteNodeTail(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);

    // if list empty
    if (handle->head == NULL) return;

    // if list has 1 element
    if (handle->head == handle->tail) {
        free(handle->head);
        handle->head = handle->tail = NULL;
        return;
    }

    // with doubly list you dont need to iterate to find second to last, because you have tail->prev
    // dont need to use temp, because you can use tail->next after changing tail addres to release deleted node
    // actualize tail
    handle->tail = handle->tail->prev;
    // free memory
    free(handle->tail->next);
    // join head and tail
    handle->tail->next = handle->head;
    handle->head->prev = handle->tail;

    --handle->capacity;
    --handle->size;
}


void dcl_deleteNodeHead(DoublyCircLinkedHandle_t handle) {
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
    // join head and tail
    handle->head->prev = handle->tail;
    handle->tail->next = handle->head;

    --handle->capacity;
    --handle->size;
}


void dcl_insertNode(DoublyCircLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);    
    assert(pData != NULL);

    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) dcl_addNodeHead(handle, pData); // handle function checks if capacity is 0
    else if (*pIndex == handle->capacity - 1) dcl_addNodeTail(handle, pData); // handle function checks if capacity is 0
    else {
        // check if its faster to iterate from the front or the back, find pointers to node on pIndex and previous
        if (*pIndex < handle->capacity/2) {
            current = handle->head;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->next;
            }
            dcl_insertBetween(handle, previous, current, pData);

        } else {
            current = handle->tail;
            for (int i = 0; i < *pIndex; ++i) {
                previous = current;
                current = current->prev;
            }
            dcl_insertBetween(handle, current, previous, pData); // !!! insertBetween function is made to take node to the left and to the right as parameters, so when
            // iterating backwards, the previous is on the right and current on the left !!!
        }

        // OR
        /* 
        current = dcl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = dcl_getNode(handle, &prev_index);
        dcl_insertBetween(previous, current, pData);
        }
        */

        // OR
        /* 
        int prev_index = *pIndex - 1;
        previous = dcl_getNode(handle, &prev_index);
        current = previous->next; // current = dcl_getNode(handle, pIndex);
        dcl_insertBetween(previous, current, pData);
        }
        */
    }

    current = NULL;
    previous = NULL;
}


void dcl_removeNode(DoublyCircLinkedHandle_t handle, const T *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);    

    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) dcl_deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) dcl_deleteNodeTail(handle);
    else {
        // erase current node
        current = dcl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = dcl_getNode(handle, &prev_index);
        dcl_removeBetween(handle, previous, current->next);

        // OR
        // erase node between previous and next
        /*
        int next_index = *pIndex + 1;
        next = dcl_getNode(handle, &next_index);
        int prev_index = *pIndex - 1;
        previous = (next->prev)->prev; // previous = dcl_getNode(handle, &prev_index);
        dcl_removeBetween(handle, previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        int prev_index = *pIndex - 1;
        previous = dcl_getNode(handle, &prev_index);
        int next_index = *pIndex + 1;
        next = (previous->next)->next;// next = dcl_getNode(handle, &next_index); 
        dcl_removeBetween(handle, previous, next);
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
            free(current);
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
            free(current);
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

        dcl_removeBetween(handle, previous, next);
        */
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}


void dcl_removeNodeElement(DoublyCircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);   
    assert(pData != NULL);

    Node *current = handle->head;
    Node *previous = NULL;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) dcl_deleteNodeHead(handle);
            else if (current == handle->tail) dcl_deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                (current->next)->prev = previous;
                // free memory
                free(current);

                // OR
                // erase current node
                dcl_removeBetween(handle, previous, current->next);
            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void dcl_print(DoublyCircLinkedHandle_t handle) {
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


int dcl_getCapacity(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->capacity;
}


int dcl_getSize(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->size;
}


Node *dcl_getHead(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->head;
}


Node *dcl_getTail(DoublyCircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->tail;
}


Node *dcl_getNode(DoublyCircLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);  

    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return dcl_getHead(handle);
    else if (*pIndex == handle->capacity - 1) return dcl_getTail(handle);
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


T dcl_getData(DoublyCircLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);  

    return dcl_getNode(handle, pIndex)->data;
}


void dcl_setData(DoublyCircLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);    
    assert(pData != NULL);

    dcl_getNode(handle, pIndex)->data = *pData;
}

void dcl_assign(DoublyCircLinkedHandle_t handle, const T *pArray, const int *pLength) {
    assert(handle != NULL);
    assert(pLength != NULL);
    assert(pArray!= NULL && *pLength > 0);
    
    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            dcl_addEmptyNodeTail(handle, &toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            dcl_deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < handle->capacity; ++i) {
        handle->dcl_setData(handle, &i, &pArray[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = pArray[i];
        current = current->next;
    }
}