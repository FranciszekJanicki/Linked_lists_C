#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdio.h>
#include <assert.h>
#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity
    int size;
} CircularLinkedList;

typedef CircularLinkedList* CircularLinkedListHandle_t;


/* returns handle (pointer) */
SinglyLinkedListHandle_t listCreateDynamic();
/* returns object */
CircularLinkedList listCreateStatic();
/* passing pointer to handle, changes what handle is pointing at */
void listCreateDynamicVoid(SinglyLinkedListHandle_t *handle, const ListConfig_t *config);
/* passing handle, changes object under handle */
void listCreateStaticVoid(CircularLinkedList *object);
/* passing handle, but it could be nice to pass ptr to Handle to point it to NULL after deallocation */
void listDelete(SinglyLinkedListHandle_t handle);

/* private methods as they do not have exception handling and should be run only inside other methods that do have it*/
void insertEmptyBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, Node* &newest);
void insertBetween(CircularLinkedListHandle_t handle, Node *left, Node *right, const T *pData);
void removeBetween(CircularLinkedListHandle_t handle, Node *left, Node *right);
void addEmptyNodeTail(CircularLinkedListHandle_t handle, Node* &newest);
void addEmptyNodeHead(CircularLinkedListHandle_t handle, Node* &newest);
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
void setpData(CircularLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(CircularLinkedListHandle_t handle, const T *array, const int &length);