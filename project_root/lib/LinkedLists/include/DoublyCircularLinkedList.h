#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} DoublyCircularLinkedList;

typedef DoublyCircularLinkedList *DoublyCircLinkedHandle_t;


/* PUBLIC 'CONSTRUCTORS/ DESTRUCTORS' */
/* return handle to dynamically allocated memory */
DoublyCircLinkedHandle_t dcl_listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyCircularLinkedList dcl_listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyCircLinkedHandle_t dcl_listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void dcl_listCreateDynamicallyVoid(DoublyCircLinkedHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void dcl_listCreateStaticallyVoid(DoublyCircLinkedHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void dcl_listDelete(DoublyCircLinkedHandle_t handle);

/* PRIVATE FUNCTIONS */
void dcl_insertEmptyBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right, Node* *newest);
void dcl_insertBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right, const T *pData);
void dcl_removeBetween(DoublyCircLinkedHandle_t handle, Node *left, Node *right);
void dcl_addEmptyNodeTail(DoublyCircLinkedHandle_t handle, Node* *newest);
void dcl_addEmptyNodeHead(DoublyCircLinkedHandle_t handle, Node* *newest);

/* PUBLIC FUNCTIONS */
void dcl_addNodeHead(DoublyCircLinkedHandle_t handle, const T *pData);
void dcl_addNodeTail(DoublyCircLinkedHandle_t handle, const T *pData);
void dcl_deleteNodeTail(DoublyCircLinkedHandle_t handle);
void dcl_deleteNodeHead(DoublyCircLinkedHandle_t handle);
void dcl_insertNode(DoublyCircLinkedHandle_t handle, const int *pIndex, const T *pData);
void dcl_removeNode(DoublyCircLinkedHandle_t handle, const T *pIndex);
void dcl_removeNodeElement(DoublyCircLinkedHandle_t handle, const T *pData);
void dcl_print(DoublyCircLinkedHandle_t handle);
int dcl_getCapacity(DoublyCircLinkedHandle_t handle);
int dcl_getSize(DoublyCircLinkedHandle_t handle);
Node *dcl_getHead(DoublyCircLinkedHandle_t handle);
Node *dcl_getTail(DoublyCircLinkedHandle_t handle);
Node *dcl_getNode(DoublyCircLinkedHandle_t handle, const int *pIndex);
T dcl_getData(DoublyCircLinkedHandle_t handle, const int *pIndex);
void dcl_setData(DoublyCircLinkedHandle_t handle, const int *pIndex, const T *pData);
void dcl_assign(DoublyCircLinkedHandle_t handle, const T *pArray, const int *pLength);


#endif // DOUBLY_CIRCULAR_LINKED_LIST_H