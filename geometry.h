#include "queue.h"


typedef queue shape; // same ol data format but new funcs :/

shape* newShape() {
    shape* s = (shape*)malloc(sizeof(shape));
    s->len = 0;
    s->front = s->rear = NULL;
    return s;
}

void shapeAddPoint(shape* s, renderpoint p) {
    struct Node* newNode = createNode(p);
    if (s->rear == NULL) {
        s->front = s->rear = newNode;
        return;
    }
    s->rear->next = newNode;
    s->rear = newNode;
    s->len++;
}

shape* rect2(renderpoint p1, renderpoint p2) {
    shape* s = newShape();

    int lgx = (p1.x > p2.x) ? p1.x : p2.x;
    int lgy = (p1.y > p2.y) ? p1.y : p2.y;
    int smx = (p1.x < p2.x) ? p1.x : p2.x;
    int smy = (p1.y < p2.y) ? p1.y : p2.y;

    for(int i = smx; i < lgx; i++) {
        shapeAddPoint(s, newrp(i, smy, p1.c));
        shapeAddPoint(s, newrp(i, lgy, p1.c));
    }

    for(int i = smy; i <= lgy; i++) {
        shapeAddPoint(s, newrp(smx, i, p1.c));
        shapeAddPoint(s, newrp(lgx, i, p1.c));
    }

    return s;
}