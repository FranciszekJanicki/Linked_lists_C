#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} SinglyLinkedList;

typedef SinglyLinkedList* SinglyLinkedListHandle_t;

/* returns handle (pointer) */
SinglyLinkedListHandle_t listCreateDynamic();
/* returns object */
SinglyLinkedList listCreateStatic();
/* passing pointer to handle, changes what handle is pointing at */
void listCreateDynamicVoid(SinglyLinkedListHandle_t *handle, const ListConfig_t *config);
/* passing handle, changes object under handle */
void listCreateStaticVoid(SinglyLinkedListHandle_t handle);
/* passing handle, but it could be nice to pass ptr to Handle to point it to NULL after deallocation */
void listDelete(SinglyLinkedListHandle_t handle);

void insertEmptyBetween(SinglyLinkedListHandle_t handle, Node *left, Node *right, Node* *pNewest);
void insertBetween(SinglyLinkedListHandle_t handle, Node *left, Node *right, const T *pData);
void removeBetween(SinglyLinkedListHandle_t handle, Node *left, Node *right);
void addEmptyNodeTail(SinglyLinkedListHandle_t handle, Node* *pNewest);
void addEmptyNodeHead(SinglyLinkedListHandle_t handle, Node* *pNewest);
void addNodeHead(SinglyLinkedListHandle_t handle, const T *pData);
void addNodeTail(SinglyLinkedListHandle_t handle, const T *pData);
void deleteNodeTail(SinglyLinkedListHandle_t handle);
void deleteNodeHead(SinglyLinkedListHandle_t handle);
void insertNode(SinglyLinkedListHandle_t handle, const int *pIndex, const T *pData);
void removeNode(SinglyLinkedListHandle_t handle, const T *pIndex);
void removeNodeElement(SinglyLinkedListHandle_t handle, const T *pData);
void print(SinglyLinkedListHandle_t handle);
int getCapacity(SinglyLinkedListHandle_t handle);
int getSize(SinglyLinkedListHandle_t handle);
Node *getHead(SinglyLinkedListHandle_t handle);
Node *getTail(SinglyLinkedListHandle_t handle);
Node *getNode(SinglyLinkedListHandle_t handle, const int *pIndex);
T getData(SinglyLinkedListHandle_t handle, const int *pIndex);
void setData(SinglyLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(SinglyLinkedListHandle_t handle, const T *array, const int *pLength);


#endif // SINGLY_LINKED_LIST_H