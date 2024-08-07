#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "CircularLinkedList.h"
#include "node.h"


/* return handle to dynamically allocated memory */
CircLinkedHandle_t cl_listCreateDynamically() {
    CircLinkedHandle_t handle = (CircLinkedHandle_t)malloc(sizeof(CircularLinkedList));
    assert(handle != NULL);
    return handle;
}

/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
CircularLinkedList cl_listCreateStatically() {
    CircularLinkedList list;
    return list;
}

/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
CircLinkedHandle_t cl_listCreateStaticStatically() {
    static CircularLinkedList list;
    CircLinkedHandle_t handle = &list;
    return handle;
}

/* dynamically allocate memory and point passed handle at it */
void cl_listCreateDynamicallyVoid(CircLinkedHandle_t *pHandle) {
    // assert that passed ptr to handle isnt NULL
    assert(pHandle != NULL);

    // allocate memory and point handle at it
    *pHandle = (CircLinkedHandle_t)malloc(sizeof(CircularLinkedList)); 
    // check if allocation succeded
    assert(*pHandle != NULL);
}

/* statically allocate memory and copy it to memory under passed handle */
void cl_listCreateStaticallyVoid(CircLinkedHandle_t handle) {
    CircularLinkedList list;
    *handle = list; // memcpy(handle, &list, sizeof(list)); // OK, COPYING STATICALLY ALLOCATED MEMORY
    // handle = &list; // WRONG!!! POINTING TO MEMORY THAT WILL GET DESTROYED AFTER THIS SCOPE RETURNS!!! APART FROM THAT 'handle' is a copy, to work on original handle would need *pHandle like above
}

/* if wanting to also free the handle pointer itself, would need to pass pointer to it, not just the copy */
void cl_listDelete(CircLinkedHandle_t handle) {
    assert(handle != NULL);
    // Node* current = handle->head;
    // for (int i = 0; i < handle->capacity; ++i) {
    //     free(current);
    //     current = current->next;
    // }
    for (int i = 0; i < handle->capacity; ++i) {
            cl_deleteNodeHead(handle);
    }

    if (handle->head != NULL) free(handle->head);
    if (handle->tail != NULL) free(handle->tail);

    free(handle);
}

void cl_insertEmptyBetween(CircLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest) {
    assert(handle != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    *pNewest = (Node *)malloc(sizeof(Node));
    (*pNewest)->next = right;
    left->next = *pNewest;

    ++handle->capacity;
}


void cl_insertBetween(CircLinkedHandle_t handle, Node *left, Node *right, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);
    assert(left != NULL && right != NULL);
    assert(left->next == right);

    Node *newest = NULL;
    cl_insertEmptyBetween(handle, left, right, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void cl_removeBetween(CircLinkedHandle_t handle, Node *left, Node *right) {
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


void cl_addEmptyNodeHead(CircLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->head == NULL) {
        (*pNewest)->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = *pNewest;
    }
    // not empty
    else {
        (*pNewest)->next = handle->head;
        // actualize head
        handle->head = *pNewest;
        handle->tail->next = handle->head;
    }

    ++handle->capacity;
}


void cl_addNodeHead(CircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    cl_addEmptyNodeHead(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;
    
    ++handle->size;
}


void cl_addEmptyNodeTail(CircLinkedHandle_t handle, Node* *pNewest) {
    assert(handle != NULL);

    *pNewest = (Node *)malloc(sizeof(Node));

    // if list empty
    if (handle->tail == NULL) {        
        (*pNewest)->next = handle->head;
        // actualize head and tail
        handle->head = handle->tail = *pNewest;
    } 
    // not empty
    else {
        (*pNewest)->next = handle->head;
        handle->tail->next = *pNewest;
        // actualize tail
        handle->tail = *pNewest;
    }

    ++handle->capacity;
}


void cl_addNodeTail(CircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *newest = NULL;
    cl_addEmptyNodeTail(handle, &newest);
    assert(newest != NULL); 
    newest->data = *pData;

    ++handle->size;
}


void cl_deleteNodeTail(CircLinkedHandle_t handle) {
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
    // find second to last 
    Node *current = handle->head;
    for (int i = 0; i < handle->capacity - 1; ++i) {
        current = current->next;
    }
    */
    // actualize tail
    handle->tail = current;
    // free memory
    free(handle->tail->next);
    handle->tail->next = handle->head;

    current = NULL;
    --handle->capacity;
    --handle->size;
}


void cl_deleteNodeHead(CircLinkedHandle_t handle) {
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
    handle->tail->next = handle->head;
    // free memory
    free(temp);

    temp = NULL;
    --handle->capacity;
    --handle->size;
    
}



void cl_insertNode(CircLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    assert(pData != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;

    if (*pIndex == 0) cl_addNodeHead(handle, pData); 
    else if (*pIndex == handle->capacity) cl_addNodeTail(handle, pData);
    else {

        // just need to find second to last to pIndex (because you can calculate current (*pIndex) by previous->next)
        // find previous index and index
        int prev_index = *pIndex - 1;
        previous = cl_getNode(handle, &prev_index);
        current = previous->next; // current = getNode(handle, pIndex);
        cl_insertBetween(handle, current, previous, pData);

        // OR
        /*
        int i = 0;
        current = handle->head;
        previous = NULL;

        for (i; i < *pIndex; ++i) {
            previous = current;
            current = current->next;
        }
        cl_insertBetween(previous, current, pData);
        */
    }
    // OR
    /* 
    int i = 0;
    current = handle->head;
    previous = NULL;

    while (current != NULL) {
        if (i == *pIndex) {
            if (current == handle->head) cl_addNodeHead(pData);
            else if (current == handle->tail) cl_addNodetail(pData);
            else {
                cl_insertBetween(previous, current, pData);
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


void cl_removeNode(CircLinkedHandle_t handle, const T *pIndex) {
    assert(handle != NULL);  
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;
    Node *previous = NULL;
    Node *next = NULL;

    if (*pIndex == 0) cl_deleteNodeHead(handle);    
    else if (*pIndex == handle->capacity - 1) cl_deleteNodeTail(handle);
    else {
        // erase current node
        current = cl_getNode(handle, pIndex);
        int prev_index = *pIndex - 1;
        previous = current->prev; // previous = getNode(handle, &prev_index);
        cl_removeBetween(handle, previous, current->next);

        // OR
        // erase node between previous and next
        /*
        int next_index = *pIndex + 1;
        next = cl_getNode(handle, &next_index);
        int prev_index = *pIndex - 1;
        previous = (next->prev)->prev; // previous = cl_getNode(handle, &prev_index);
        cl_removeBetween(handle, previous, next);
        */

        // OR
        // erase node between previous and next
        /*
        int prev_index = *pIndex - 1;
        previous = cl_getNode(handle, &prev_index);
        int next_index = *pIndex + 1;
        next = (previous->next)->next;// next = cl_getNode(handle, &next_index); 
        cl_removeBetween(handle, previous, next);
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

        cl_removeBetween(handle, previous, next);
        */
    }

    current = NULL;
    previous = NULL;
    next = NULL;
}



void cl_removeNodeElement(CircLinkedHandle_t handle, const T *pData) {
    assert(handle != NULL);
    assert(pData != NULL);

    Node *current = handle->head;
    Node *previous = NULL;
    int i = 0;

    while (current != NULL) {
        
        if (current->data == *pData) {
            if (current == handle->head) cl_deleteNodeHead(handle);
            else if (current == handle->tail) cl_deleteNodeTail(handle);
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
                // cl_removeBetween(previous, current->next);

            }
            // return; // dont stop iterating, remove all nodes with handle pData
        }

        previous = current;
        current = current->next;
    }

    previous = NULL;
    current = NULL;
}


void cl_print(CircLinkedHandle_t handle) {
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


int cl_getCapacity(CircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->capacity;
}


int cl_getSize(CircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->size;
}


Node *cl_getHead(CircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->head;
}


Node *cl_getTail(CircLinkedHandle_t handle) {
    assert(handle != NULL);

    return handle->tail;
}


Node *cl_getNode(CircLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    // handle incorrect pIndex, wont have to worry later
    assert(*pIndex >= 0 && *pIndex < handle->capacity);

    Node *current = NULL;

    if (*pIndex == 0) return cl_getHead(handle);
    else if (*pIndex == handle->capacity - 1) return cl_getTail(handle);
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


T cl_getData(CircLinkedHandle_t handle, const int *pIndex) {
    assert(handle != NULL);
    assert(pIndex != NULL);

    return cl_getNode(handle, pIndex)->data;
}


void cl_setData(CircLinkedHandle_t handle, const int *pIndex, const T *pData) {
    assert(handle != NULL);
    assert(pIndex != NULL);
    assert(pData != NULL);

    cl_getNode(handle, pIndex)->data = *pData;
}


void cl_assign(CircLinkedHandle_t handle, const T *pArray, const int *pLength) {
    assert(handle != NULL);
    assert(pLength != NULL);
    assert(pArray!= NULL && *pLength > 0);
    
    // resize
    int sizeDifference = *pLength - handle->capacity;
    int i;
    if (sizeDifference > 0) {    
        for (i = 0; i < sizeDifference; ++i) {
            Node *toAdd = NULL;
            cl_addEmptyNodeTail(handle, &toAdd);
        }
    } else if (sizeDifference < 0) {
        for (i = 0; i < -sizeDifference; ++i) {
            cl_deleteNodeTail(handle);
        }
    }

    /* handle has shitty complexity as every iteration will call getNode function, which iterates to the pIndex*/
    /* for (i = 0; i < handle->capacity; ++i) {
        handle->cl_setData(handle, &i, &pArray[i]);
    } 
    */
    Node *current = handle->head;
    for (i = 0; i < handle->capacity; ++i) {
        current->data = pArray[i];
        current = current->next;
    }
}