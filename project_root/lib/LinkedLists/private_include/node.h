#ifndef NODE_H
#define NODE_H

typedef int T;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    T data;
} Node;


typedef struct {
    int capacity;
    int size;
} ListConfig_t;


#endif // NODE_H
