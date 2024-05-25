#include <stdlib.h>
#include <stdbool.h>

struct Node {
    struct Node *next;
    void *data;
};

struct Queue {
    struct Node *head;
    struct Node *tail;
};



void enqueue(struct Queue *q, void *data); 

bool isQueueEmpty(struct Queue *queue); 

struct Node *dequeue(struct Queue *q);

