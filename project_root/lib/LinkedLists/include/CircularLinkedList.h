#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} CircularLinkedList;

typedef CircularLinkedList *CircLinkedHandle_t;

/* PUBLIC 'CONSTRUCTORS/ DESTRUCTORS' */
/* return handle to dynamically allocated memory */
CircLinkedHandle_t cl_listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
CircularLinkedList cl_listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
CircLinkedHandle_t cl_listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void cl_listCreateDynamicallyVoid(CircLinkedHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void cl_listCreateStaticallyVoid(CircLinkedHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void cl_listDelete(CircLinkedHandle_t handle);

/* PRIVATE FUNCTIONS */
void cl_insertEmptyBetween(CircLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest);
void cl_insertBetween(CircLinkedHandle_t handle, Node *left, Node *right, const T *pData);
void cl_removeBetween(CircLinkedHandle_t handle, Node *left, Node *right);
void cl_addEmptyNodeTail(CircLinkedHandle_t handle, Node* *pNewest);
void cl_addEmptyNodeHead(CircLinkedHandle_t handle, Node* *pNewest);

/* PUBLIC FUNCTIONS */
void cl_addNodeHead(CircLinkedHandle_t handle, const T *pData);
void cl_addNodeTail(CircLinkedHandle_t handle, const T *pData);
void cl_deleteNodeTail(CircLinkedHandle_t handle);
void cl_deleteNodeHead(CircLinkedHandle_t handle);
void cl_insertNode(CircLinkedHandle_t handle, const int *pIndex, const T *pData);
void cl_removeNode(CircLinkedHandle_t handle, const T *pIndex);
void cl_removeNodeElement(CircLinkedHandle_t handle, const T *pData);
void cl_print(CircLinkedHandle_t handle);
int cl_getCapacity(CircLinkedHandle_t handle);
int cl_getSize(CircLinkedHandle_t handle);
Node *cl_getHead(CircLinkedHandle_t handle);
Node *cl_getTail(CircLinkedHandle_t handle);
Node *cl_getNode(CircLinkedHandle_t handle, const int *pIndex);
T cl_getData(CircLinkedHandle_t handle, const int *pIndex);
void cl_setData(CircLinkedHandle_t handle, const int *pIndex, const T *pData);
void cl_assign(CircLinkedHandle_t handle, const T *pArray, const int *pLength);


#endif // CIRCULAR_LINKED_LIST_H