#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include "node.h"


typedef struct {
    Node *head;
    Node *tail;
    int capacity;
    int size;
} DoublyCircularLinkedList;

typedef DoublyCircularLinkedList *DoublyCircularLinkedListHandle_t;



/* return handle to dynamically allocated memory */
DoublyCircularLinkedListHandle_t listCreateDynamically();
/* return statically allocated memory (statically allocated- either copy it somewhere (like here to return variable) or make it static!)*/
DoublyCircularLinkedList listCreateStatically();
/* return pointer to statically allocated static memory (statically allocated- either copy it somwehwere or make it static (like here to be able to not copy it and take pointer, without static keyword this staically alloated memory would vanish!)!) */
DoublyCircularLinkedListHandle_t listCreateStaticStatically();
/* dynamically allocate memory and point passed handle at it */
void listCreateDynamicallyVoid(DoublyCircularLinkedListHandle_t *pHandle);
/* statically allocate memory and copy it to memory under passed handle */
void listCreateStaticallyVoid(DoublyCircularLinkedListHandle_t handle);
/* need a pointer to handle in case memory under handle was allocated dynamically! */
void listDelete(DoublyCircularLinkedListHandle_t handle);
void insertEmptyBetween(DoublyCircularLinkedListHandle_t handle, Node *left, Node *right, Node* *newest);
void insertBetween(DoublyCircularLinkedListHandle_t handle, Node *left, Node *right, const T *pData);
void removeBetween(DoublyCircularLinkedListHandle_t handle, Node *left, Node *right);
void addEmptyNodeTail(DoublyCircularLinkedListHandle_t handle, Node* *newest);
void addEmptyNodeHead(DoublyCircularLinkedListHandle_t handle, Node* *newest);
void addNodeHead(DoublyCircularLinkedListHandle_t handle, const T *pData);
void addNodeTail(DoublyCircularLinkedListHandle_t handle, const T *pData);
void deleteNodeTail(DoublyCircularLinkedListHandle_t handle);
void deleteNodeHead(DoublyCircularLinkedListHandle_t handle);
void insertNode(DoublyCircularLinkedListHandle_t handle, const int *pIndex, const T *pData);
void removeNode(DoublyCircularLinkedListHandle_t handle, const T *pIndex);
void removeNodeElement(DoublyCircularLinkedListHandle_t handle, const T *pData);
void print(DoublyCircularLinkedListHandle_t handle);
int getCapacity(DoublyCircularLinkedListHandle_t handle);
int getSize(DoublyCircularLinkedListHandle_t handle);
Node *getHead(DoublyCircularLinkedListHandle_t handle);
Node *getTail(DoublyCircularLinkedListHandle_t handle);
Node *getNode(DoublyCircularLinkedListHandle_t handle, const int *pIndex);
T getData(DoublyCircularLinkedListHandle_t handle, const int *pIndex);
void setData(DoublyCircularLinkedListHandle_t handle, const int *pIndex, const T *pData);
void assign(DoublyCircularLinkedListHandle_t handle, const T *pArray, const int *pLength);


#endif // DOUBLY_CIRCULAR_LINKED_LIST_H