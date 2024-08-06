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

/* return handle to dynamically allocated memory */
SinglyLinkedListHandle_t listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
SinglyLinkedList listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
SinglyLinkedListHandle_t listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void listCreateDynamicallyVoid(SinglyLinkedListHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void listCreateStaticallyVoid(SinglyLinkedListHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
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