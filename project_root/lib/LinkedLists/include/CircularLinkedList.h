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

typedef CircularLinkedList* CircularLinkedListHandle_t;


/* return handle to dynamically allocated memory */
CircularLinkedListHandle_t listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
CircularLinkedList listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
CircularLinkedListHandle_t listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void listCreateDynamicallyVoid(CircularLinkedListHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void listCreateStaticallyVoid(CircularLinkedListHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void listDelete(CircularLinkedListHandle_t handle);
void insertEmptyBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, Node* *pNewest);
void insertBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, const T *pData);
void removeBetween(CircularLinkedListHandle_t handle, Node *left, Node *right);
void addEmptyNodeTail(CircularLinkedListHandle_t handle, Node* *pNewest);
void addEmptyNodeHead(CircularLinkedListHandle_t handle, Node* *pNewest);
void addNodeHead(CircularLinkedListHandle_t handle, const T *pData);
void addNodeTail(CircularLinkedListHandle_t handle, const T *pData);
void deleteNodeTail(CircularLinkedListHandle_t handle);
void deleteNodeHead(CircularLinkedListHandle_t handle);
void insertNode(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData);
void removeNode(CircularLinkedListHandle_t handle, const T *pIndex);
void removeNodeElement(CircularLinkedListHandle_t handle, const T *pData);
void print(CircularLinkedListHandle_t handle);
int getCapacity(CircularLinkedListHandle_t handle);
int getSize(CircularLinkedListHandle_t handle);
Node *getHead(CircularLinkedListHandle_t handle);
Node *getTail(CircularLinkedListHandle_t handle);
Node *getNode(CircularLinkedListHandle_t handle, const int *pIndex);
T getpData(CircularLinkedListHandle_t handle, const int *pIndex);
void setData(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(CircularLinkedListHandle_t handle, const T *array, const int *pLength);


#endif // CIRCULAR_LINKED_LIST_H