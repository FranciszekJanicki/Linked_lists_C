#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} SinglyLinkedList;

typedef SinglyLinkedList *SinglyLinkedHandle_t;

/* PUBLIC 'CONSTRUCTORS/ DESTRUCTORS' */
/* return handle to dynamically allocated memory */
SinglyLinkedHandle_t sl_listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
SinglyLinkedList sl_listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
SinglyLinkedHandle_t sl_listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void sl_listCreateDynamicallyVoid(SinglyLinkedHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void sl_listCreateStaticallyVoid(SinglyLinkedHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void sl_listDelete(SinglyLinkedHandle_t handle);

/* PRIVATE FUNCTIONS */
void sl_insertEmptyBetween(SinglyLinkedHandle_t handle, Node *left, Node *right, Node* *pNewest);
void sl_insertBetween(SinglyLinkedHandle_t handle, Node *left, Node *right, const T *pData);
void sl_removeBetween(SinglyLinkedHandle_t handle, Node *left, Node *right);
void sl_addEmptyNodeTail(SinglyLinkedHandle_t handle, Node* *pNewest);
void sl_addEmptyNodeHead(SinglyLinkedHandle_t handle, Node* *pNewest);

/* PUBLIC FUNCTIONS */
void sl_addNodeHead(SinglyLinkedHandle_t handle, const T *pData);
void sl_addNodeTail(SinglyLinkedHandle_t handle, const T *pData);
void sl_deleteNodeTail(SinglyLinkedHandle_t handle);
void sl_deleteNodeHead(SinglyLinkedHandle_t handle);
void sl_insertNode(SinglyLinkedHandle_t handle, const int *pIndex, const T *pData);
void sl_removeNode(SinglyLinkedHandle_t handle, const T *pIndex);
void sl_removeNodeElement(SinglyLinkedHandle_t handle, const T *pData);
void sl_print(SinglyLinkedHandle_t handle);
int sl_getCapacity(SinglyLinkedHandle_t handle);
int sl_getSize(SinglyLinkedHandle_t handle);
Node *sl_getHead(SinglyLinkedHandle_t handle);
Node *sl_getTail(SinglyLinkedHandle_t handle);
Node *sl_getNode(SinglyLinkedHandle_t handle, const int *pIndex);
T sl_getData(SinglyLinkedHandle_t handle, const int *pIndex);
void sl_setData(SinglyLinkedHandle_t handle, const int *pIndex, const T *pData);
void sl_assign(SinglyLinkedHandle_t handle, const T *pArray, const int *pLength);


#endif // SINGLY_LINKED_LIST_H