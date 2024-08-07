#include "SinglyLinkedList.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "node.h"


/* return handle to dynamically allocated memory */
SinglyLinkedHandle_t sl_listCreateDynamically() {
    SinglyLinkedHandle_t handle = (SinglyLinkedHandle_t)malloc(sizeof(SinglyLinkedList));
    assert(handle != NULL);
    return handle;
}

/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
SinglyLinkedList sl_listCreateStatically() {
    SinglyLinkedList list;
    return list;
}

/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
SinglyLinkedHandle_t sl_listCreateStaticStatically() {
    static SinglyLinkedList list;
    SinglyLinkedHandle_t handle = &list;
    return handle;
}

/* dynamically allocate memory and point passed handle at it */
void sl_listCreateDynamicallyVoid(SinglyLinkedHandle_t *pHandle) {
    // assert that passed ptr to handle isnt NULL
    assert(pHandle != NULL);

    // allocate memory and point handle at it
    *pHandle = (SinglyLinkedHandle_t)malloc(sizeof(SinglyLinkedList));
    // check if allocation succeded
    assert(*pHandle != NULL);
}

/* statically allocate memory and copy it to memory under passed handle */
void sl_listCreateStaticallyVoid(SinglyLinkedHandle_t handle) {
    SinglyLinkedList list;
    *handle = list; // memcpy(handle, &list, sizeof(list)); // OK, COPYING STATICALLY ALLOCATED MEMORY
    // handle = &list; // WRONG!!! POINTING TO MEMORY THAT WILL GET DESTROYED AFTER THIS SCOPE RETURNS!!! APART FROM THAT 'handle' is a copy, to work on original handle would need *pHandle like above
}

/* if wanting to also free the handle pointer itself, would need to pass pointer to it, not just the copy */
void sl_listDelete(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);
    // Node* current = handle->head;
    // for (int i = 0; i < handle->capacity; ++i) {
    //     free(current);
    //     current = current->next;
    // }
    for (int i = 0; i < handle->capacity; ++i) {
            sl_deleteNodeHead(handle);
    }

    if (handle->head != NULL) free(handle->head);
    if (handle->tail != NULL) free(handle->tail);

    free(handle);
}

void sl_insertEmptyBetween(SinglyLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest) {
    assert(pNewest != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    *pNewest = (Node *)malloc(sizeof(Node));
    (*pNewest)->next = right;
    left->next = *pNewest;

    ++handle->capacity;
}


void sl_insertBetween(SinglyLinkedHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(left != NULL && right != NULL);
    assert(left->next == right);
    assert(pData != NULL);

    Node *newest = NULL;
    sl_insertEmptyBetween(handle, left, right, &newest);
    assert(newest != NULL);
    newest->data = *pData;

    ++handle->size;
}


void sl_removeBetween(SinglyLinkedHandle_t handle, Node *left, Node *right) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next->next == right);

    // free memory
    free(left->next);
    // join left and right
    left->next = right;
    
    --handle->size;
    --handle->capacity;
}


void sl_addEmptyNodeHead(SinglyLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    // in single list dont have to check if list is empty or not for head insertion
    *pNewest = (Node *)malloc(sizeof(Node));
    (*pNewest)->next = handle->head;
    // actualize head
    handle->head = *pNewest;

    ++handle->capacity;
}


void sl_addNodeHead(SinglyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    sl_addEmptyNodeHead(handle, &newest);
    assert(newest != NULL);
    newest->data = *pData;
    
    ++handle->size;
}


void sl_addEmptyNodeTail(SinglyLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->tail == NULL) {        
        (*pNewest)->next = NULL;
        // actualize tail
        handle->tail = *pNewest;
    } 
    // not empty
    else {
        (*pNewest)->next = NULL;
        handle->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;
    }

    ++handle->capacity;
}

void sl_addNodeTail(SinglyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    sl_addEmptyNodeTail(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void sl_deleteNodeTail(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);

    // if list empty
    if (handle->head == NULL) return;

    // if list has 1 element
    if (handle->head == handle->tail) {
        free(handle->head);
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
    // if list empty
    if (capacity == 0) return;

    // if list has 1 element
    if (capacity == 1) {
        free(head;
        head = tail = NULL;
        return;
    }

    // find second to last 
    Node *current = head;
    for (int i = 0; i < capacity - 1; ++i) {
        current = current->next;
    }
    */
    // actualize tail
    handle->tail = current;
    // free memory
    free(handle->tail->next);
    // actualize tail edge
    handle->tail->next = NULL;

    current = NULL;

    --handle->capacity;
    --handle->size;
}


void sl_deleteNodeHead(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);

    // if list empty
    if (handle->capacity == 0) return;

    // if list has 1 element
    if (handle->capacity == 1) {
        free(handle->head);
        handle->head = handle->tail = NULL;
        return;
    }

    Node *temp = handle->head;
    // actualize head
    handle->head = handle->head->next;
    // free memory
    free(temp);
    temp = NULL;

    --handle->capacity;
    --handle->size;
}


void sl_insertNode(SinglyLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    assert(pData != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) sl_addNodeHead(handle, pData); 
    else if (*pIndex == handle->capacity) sl_addNodeTail(handle, pData);
    else {

        // just need to find second to last to pIndex (because you can calculate current (*pIndex) by previous->next)
        // find previous index and index
        int prev_index = *pIndex - 1;
        previous = sl_getNode(handle, &prev_index);
        current = previous->next; // current = sl_getNode(handle, pIndex);
        sl_insertBetween(handle, previous, current, pData);

        // OR
        /*
        int i = 0;
        current = handle->head;
        previous = NULL;

        for (i; i < *pIndex; ++i) {
            previous = current;
            current = current->next;
        }
        sl_insertBetween(handle, previous, current, pData);
        */
    }
    // OR
    /* 
    int i = 0;
    current = head;
    previous = NULL;

    while (current != NULL) {
        if (i == *pIndex) {
            if (current == handle->head) sl_addNodeHead(handle, pData);
            else if (current == handle->tail) sl_addNodetail(handle, pData);
            else {
                sl_insertBetween(handle, previous, current, pData);
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


void sl_removeNode(SinglyLinkedHandle_t handle, const T *pIndex) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) sl_deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) sl_deleteNodeTail(handle);
    else {
        // erase current node
        current = sl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = sl_getNode(handle, &prev_index);
        sl_removeBetween(handle, previous, current->next);

        // OR
        // erase node between previous and next
        /*
        int next_index = *pIndex + 1;
        next = sl_getNode(handle, &next_index);
        int prev_index = *pIndex - 1;
        previous = (next->prev)->prev; // previous = sl_getNode(handle, &prev_index);
        sl_removeBetween(handle, previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        int prev_index = *pIndex - 1;
        previous = sl_getNode(handle, &prev_index);
        int next_index = *pIndex + 1;
        next = (previous->next)->next;// next = sl_getNode(handle, &next_index); 
        sl_removeBetween(handle, previous, next);
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

        sl_removeBetween(handle, previous, next);
        */
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}



void sl_removeNodeElement(SinglyLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);
    Node *current = handle->head;
    Node *previous = NULL;
    int i = 0;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) sl_deleteNodeHead(handle);
            else if (current == handle->tail) sl_deleteNodeTail(handle);
            else {
                // erase current node
                // join previous and next to current
                previous->next = current->next;
                // free memory
                free(current);
                --handle->capacity;
                --handle->size;

                // OR
                // erase current node
                // sl_removeBetween(handle, previous, current->next);

            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void sl_print(SinglyLinkedHandle_t handle) {
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


int sl_getCapacity(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);
    return handle->capacity;
}


int sl_getSize(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);
    return handle->size;
}


Node *sl_getHead(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);
    return handle->head;
}


Node *sl_getTail(SinglyLinkedHandle_t handle) {
    assert(handle != NULL);
    return handle->tail;
}


Node *sl_getNode(SinglyLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return sl_getHead(handle);
    else if (*pIndex == handle->capacity - 1) return sl_getTail(handle);
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

T sl_getData(SinglyLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    return sl_getNode(handle, pIndex)->data;
}

void sl_setData(SinglyLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);    
    assert(pData != NULL);
    sl_getNode(handle, pIndex)->data = *pData;
}

void sl_assign(SinglyLinkedHandle_t handle, const T *pArray, const int *pLength) {
    assert(handle != NULL);
    assert(pLength != NULL);
    assert(pArray!= NULL && *pLength > 0);
    
    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            sl_addEmptyNodeTail(handle, &toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            sl_deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < handle->capacity; ++i) {
        handle->sl_setData(handle, &i, &pArray[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = pArray[i];
        current = current->next;
    }
}