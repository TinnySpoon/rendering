#include <stdlib.h>


typedef struct {
    int x, y;
    char c;
} renderpoint;
#define RPNULL (renderpoint){-1,-1,-1}
#define RP0 (renderpoint) {0,0,' '}
#define RPFLNULL (renderpointfl){-1,-1,-1}
#define RPFL0 (renderpointfl) {0,0,' '}

typedef struct {
    float x, y;
    char c;
} renderpointfl;

// new renderpoint
renderpoint newrp(int x, int y, char c) { return (renderpoint){x,y,c}; }
// new renderpointfl
renderpointfl newrpfl(float x, float y, char c) { return (renderpointfl){x,y,c}; }
// renderpointfl to renderpoint
renderpoint rpfltorp(renderpointfl p) { return (renderpoint){p.x,p.y,p.c}; }
// renderpoint to renderpointfl
renderpointfl rptorpfl(renderpoint p) { return (renderpointfl){p.x,p.y,p.c}; }



// Define the structure of a node in the queue
struct Node {
    renderpoint data;
    struct Node* next;
};

// Define the structure of the queue
typedef struct Queue {
    int len;
    struct Node* front;
    struct Node* rear;
} queue;

// Function to create a new node
struct Node* createNode(renderpoint data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        // printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        // printf("Memory allocation failed\n");
        exit(1);
    }
    queue->len = 1;
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, renderpoint data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
    queue->len++;
}

// Function to dequeue an element from the queue
renderpoint dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return RPNULL;
    }
    struct Node* temp = queue->front;
    renderpoint data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->len--;
    return data;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void clearQueue(struct Queue *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

void freeQueue(struct Queue* queue) {
    clearQueue(queue);
    free(queue);
}