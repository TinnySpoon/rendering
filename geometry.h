#include "queue.h"
#include <math.h>

#define PITHREE 1.0471975512
#define TWOPITHREE 2.09439510239
#define FOURPITHREE 4.18879020479


typedef queue shape;

shape* newShape() {
    shape* s = (shape*)malloc(sizeof(shape));
    s->len = 0;
    s->front = s->rear = NULL;
    return s;
}

void shapeFree(shape* s) {
    while(s->front != NULL) {
        struct Node* n = s->front;
        s->front = s->front->next;
        free(n);
    }

    free(s);
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

void shapeAddShape(shape* s1, shape* s2) {
    struct Node* n = s2->front;
    while(n != NULL) {
        shapeAddPoint(s1, n->data);
        n = n->next;
    }
}


renderpointfl renderpointflRotate(renderpointfl p, renderpointfl rotationPoint, float angle) {
    printf("p.x = %f\n", p.x);
    printf("p.y = %f\n", p.y);
    float nx = p.x - rotationPoint.x;
    float ny = p.y - rotationPoint.y;

    printf("p.x = %f\n", p.x);
    printf("p.y = %f\n", p.y);

    float anglesin = sin(angle);
    float anglecos = cos(angle);
    printf("anglesin = %f\n", anglesin);
    printf("anglecos = %f\n", anglecos);

    p.x = nx * anglecos - ny * anglesin + rotationPoint.x;
    p.y = nx * anglesin - ny * anglecos + rotationPoint.y;

    printf("p.x = %f\n", p.x);
    printf("p.y = %f\n", p.y);

    return p;
}



shape* lineint(renderpoint p1, renderpoint p2) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);

    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;

    int err = dx - dy;
    int e2;
    shape* s = newShape();

    while(true) {
        shapeAddPoint(s, p1);

        if(p1.x == p2.x && p1.y == p2.y) break;
        e2 = 2*err;
        if(e2 > -dy) {
            err -= dy;
            p1.x += sx;
        }
        if(e2 < dx) {
            err += dx;
            p1.y += sy;
        }
    }

    return s;
}

shape* line(renderpointfl p1, renderpointfl p2) { return lineint(rpfltorp(p1), rpfltorp(p2)); }


shape* rect2(renderpointfl p1, renderpointfl p2) {
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

shape* rect4(renderpointfl p1, renderpointfl p2, renderpointfl p3, renderpointfl p4) {

    shape* rect = line(p1, p2); // just use the first line as the rectangle object
    shape* l2 = line(p2, p3);
    shape* l3 = line(p3, p4);
    shape* l4 = line(p4, p1);

    shapeAddShape(rect, l2);
    shapeAddShape(rect, l3);
    shapeAddShape(rect, l4);

    shapeFree(l2);
    shapeFree(l3);
    shapeFree(l4);
    

    return rect;
}

shape* eqtriangle(renderpointfl center, float radius, float rotation) {
    renderpointfl p1 = renderpointflRotate(newrpfl(0, radius, '0'), center, rotation);
    renderpointfl p2 = renderpointflRotate(newrpfl(0, radius, '0'), center, rotation + TWOPITHREE);
    renderpointfl p3 = renderpointflRotate(newrpfl(0, radius, '0'), center, rotation + FOURPITHREE);

    shape* triangle = line(p1, p2);
    shape* l2 = line(p2, p3);
    shape* l3 = line(p3, p1);

    shapeAddShape(triangle, l2);
    shapeAddShape(triangle, l3);

    shapeFree(l2);
    shapeFree(l3);

    return triangle;
}

float constrain_angle(float angle) {
    // Ensure the angle is positive
    while (angle < 0) {
        angle += 2 * M_PI;
    }

    // Ensure the angle is within the range [0, 2*pi)
    while (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }

    return angle;
}


