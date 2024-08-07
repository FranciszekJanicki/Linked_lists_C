#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} DoublyLinkedList;

typedef DoublyLinkedList *DoublyLinkedHandle_t;

/* PUBLIC 'CONSTRUCTORS/ DESTRUCTORS' */
/* return handle to dynamically allocated memory */
DoublyLinkedHandle_t dl_listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyLinkedList dl_listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyLinkedHandle_t dl_listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void dl_listCreateDynamicallyVoid(DoublyLinkedHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void dl_listCreateStaticallyVoid(DoublyLinkedHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void dl_listDelete(DoublyLinkedHandle_t handle);

/* PRIVATE FUNCTIONS */
void dl_insertEmptyBetween(DoublyLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest);
void dl_insertBetween(DoublyLinkedHandle_t handle, Node *left, Node *right, const T *pData);
void dl_removeBetween(DoublyLinkedHandle_t handle, Node *left, Node *right);
void dl_addEmptyNodeTail(DoublyLinkedHandle_t handle, Node* *pNewest);
void dl_addEmptyNodeHead(DoublyLinkedHandle_t handle, Node* *pNewest);

/* PUBLIC FUNCTIONS */
void dl_addNodeHead(DoublyLinkedHandle_t handle, const T *pData);
void dl_addNodeTail(DoublyLinkedHandle_t handle, const T *pData);
void dl_deleteNodeTail(DoublyLinkedHandle_t handle);
void dl_deleteNodeHead(DoublyLinkedHandle_t handle);
void dl_insertNode(DoublyLinkedHandle_t handle, const int *pIndex, const T *pData);
void dl_removeNode(DoublyLinkedHandle_t handle, const T *pIndex);
void dl_removeNodeElement(DoublyLinkedHandle_t handle, const T *pData);
void dl_print(DoublyLinkedHandle_t handle);
int dl_getCapacity(DoublyLinkedHandle_t handle);
int dl_getSize(DoublyLinkedHandle_t handle);
Node *dl_getHead(DoublyLinkedHandle_t handle);
Node *dl_getTail(DoublyLinkedHandle_t handle);
Node *dl_getNode(DoublyLinkedHandle_t handle, const int *pIndex);
T dl_getData(DoublyLinkedHandle_t handle, const int *pIndex);
void dl_setData(DoublyLinkedHandle_t handle, const int *pIndex, const T *pData);
void dl_assign(DoublyLinkedHandle_t handle, const T *pArray, const int *pLength);


#endif // DOUBLY_LINKED_LIST_H