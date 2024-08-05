#ifndef DOUBLY_CIRCULAR_LINKED_LIST_H
#define DOUBLY_CIRCULAR_LINKED_LIST_H

#include "node.h"


typedef struct {
    private:
        Node *head;
        Node *tail;
        int capacity;
        int size;
} DoublyCircularLinkedList;

typedef DoublyCircularLinkedList* DoublyCircularLinkedListHandle_t;


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
void setData(DoublyCircularLinkedListHandle_t handle, const int *pIndex, const T pData);
void assign(DoublyCircularLinkedListHandle_t handle, const T *array, const int *pLength);


#endif // DOUBLY_CIRCULAR_LINKED_LIST_H