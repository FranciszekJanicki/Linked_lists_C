#ifndef NODE_H
#define NODE_H

typedef int T;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    T data;
} Node;

typedef Node *NodeHandle_t;

#endif // NODE_H
