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

/* private methods as they do not have exception handling and should be run only inside other methods that do have it*/
void insertEmptyBetween(Node *left, Node *right, Node* &newest);
void insertBetween(Node *left, Node *right, const T *data);
void removeBetween(Node *left, Node *right);
void addEmptyNodeTail(Node* &newest);
void addEmptyNodeHead(Node* &newest);
void addNodeHead(const T *data);
void addNodeTail(const T *data);
void deleteNodeTail();
void deleteNodeHead();
void insertNode(const int &index, const T *data);
void removeNode(const T &index);
void removeNodeElement(const T *data);
void print();
int getCapacity();
int getSize();
Node *getHead();
Node *getTail();
Node *getNode(const int &index);
T getData(const int &index);
void setData(const int &index, const T *data);
void assign(const T *array, const int &length);