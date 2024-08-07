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

typedef DoublyLinkedList *DoublyLinkedListHandle_t;


/* return handle to dynamically allocated memory */
DoublyLinkedListHandle_t listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyLinkedList listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyLinkedListHandle_t listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void listCreateDynamicallyVoid(DoublyLinkedListHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void listCreateStaticallyVoid(DoublyLinkedListHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void listDelete(DoublyLinkedListHandle_t handle);
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
int getCapacity(DoublyLinkedListHandle_t handle);
int getSize(DoublyLinkedListHandle_t handle);
Node *getHead(DoublyLinkedListHandle_t handle);
Node *getTail(DoublyLinkedListHandle_t handle);
Node *getNode(DoublyLinkedListHandle_t handle, const int *pIndex);
T getData(DoublyLinkedListHandle_t handle, const int *pIndex);
void setData(DoublyLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(DoublyLinkedListHandle_t handle, const T *pArray, const int *pLength);


#endif // DOUBLY_LINKED_LIST_H