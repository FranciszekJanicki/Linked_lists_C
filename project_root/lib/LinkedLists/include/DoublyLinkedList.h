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

typedef DoublyLinkedList* DoublyLinkedListHandle_t;


/* returns handle (pointer) */
SinglyLinkedListHandle_t listCreateDynamic();
/* returns object */
SinglyLinkedList listCreateStatic();
/* passing pointer to handle, changes what handle is pointing at */
void listCreateDynamicVoid(SinglyLinkedListHandle_t *handle, const ListConfig_t *config);
/* passing handle, changes object under handle */
void listCreateStaticVoid(SinglyLinkedList *object);
/* passing handle, but it could be nice to pass ptr to Handle to point it to NULL after deallocation */
void listDelete(SinglyLinkedListHandle_t handle);

/* private methods as they do not have exception handling and should be run only inside other methods that do have it*/
void insertEmptyBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, Node* *pNewest);
void insertBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right, const T *pData);
void removeBetween(DoublyLinkedListHandle_t handle, Node *left, Node *right);
void addEmptyNodeTail(DoublyLinkedListHandle_t handle, Node* *pNewest);
void addEmptyNodeHead(DoublyLinkedListHandle_t handle, Node* *pNewest);
void addNodeHead(DoublyLinkedListHandle_t handle, const T *pData);
void addNodeTail(DoublyLinkedListHandle_t handle, const T *pData);
void deleteNodeTail(DoublyLinkedListHandle_t handle);
void deleteNodeHead(DoublyLinkedListHandle_t handle);
void insertNode(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData);
void removeNode(DoublyLinkedListHandle_t handle, const T *pIndex);
void removeNodeElement(DoublyLinkedListHandle_t handle, const T *pData);
void print(DoublyLinkedListHandle_t handle);
int getCapacity();
int getSize(DoublyLinkedListHandle_t handle);
Node *getHead();
Node *getTail(DoublyLinkedListHandle_t handle);
Node *getNode(DoublyLinkedListHandle_t handle, const int *pIndex);
T getData(DoublyLinkedListHandle_t handle, const int *pIndex);
void setData(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(DoublyLinkedListHandle_t handle, const T *array, const int *pLength);


#endif // DOUBLY_LINKED_LIST_H