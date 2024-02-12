// #include <stdlib.h>
#include <stdbool.h>


int screenWidth, screenHeight;
#ifdef __linux__
	#include <unistd.h>
    #include <X11/Xlib.h>
#elif _WIN32
    #include <time.h>
    #include <windows.h>

    void usleep(unsigned long microseconds) {
        struct timespec ts;
        ts.tv_sec = microseconds / 1000000;
        ts.tv_nsec = (microseconds % 1000000) * 1000;

        while (nanosleep(&ts, &ts) == -1);
    }

#endif




#include "geometry.h"

#define WINDX(w, x, y) w->buffer[y + x*w->sizeY]

typedef struct {
    int sizeX;
    int sizeY;
    int offsetX;
    int offsetY;
    queue* points;
    char* buffer;
} window;

window* newWindowFixedSize() { // TODO fix sizing and test for linux
    #ifdef __linux__
        Display* display = XOpenDisplay(NULL);
        Screen* screen = DefaultScreenOfDisplay(display);

        int screenWidth = WidthOfScreen(screen);
        int screenHeight = HeightOfScreen(screen);

        XCloseDisplay(display);
    #elif _WIN32
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    #endif
}

window* newWindow(int sizeX, int sizeY) {
    printf("\033[2J");
    sizeY++; // dont ask me what the problem is idrk but this helps at least
    window* w = malloc(sizeof(window));
    w->sizeX = sizeX;
    w->sizeY = sizeY-1;
    w->offsetX = sizeX/2;
    w->offsetY = sizeY/2-1;
    w->points = createQueue();
    w->buffer = malloc(sizeof(char) * sizeX * sizeY); // puts buffer into that allocated memory
    for(int i = 0; i < (sizeX) * (sizeY); i++) w->buffer[i] = ' ';

    return w;
}

void windowClear(window* w) { for(int i = 0; i < (w->sizeX) * (w->sizeY); i++) w->buffer[i] = ' '; }

void windowClearPoints(window* w) { clearQueue(w->points); }

bool windowPushPoint(window* w, renderpoint p) {
    p.x += w->offsetX;
    p.y = w->offsetY - p.y;
    if(p.x < 0 || p.x > w->sizeX-1) return false;
    if(p.y < 0 || p.y > w->sizeY-1) return false;
    enqueue(w->points, p);
    return true;
}

renderpoint windowPopPoint(window* w) {
    return dequeue(w->points);
}

bool windowSetPoint(window* w, renderpoint p) {
    p.x += w->offsetX;
    p.y = w->offsetY - p.y;
    if(p.x < 0 || p.x > w->sizeX-1) return false;
    if(p.y < 0 || p.y > w->sizeY-1) return false;
    w->buffer[p.y + p.x*w->sizeY] = p.c;
    return true;
}

bool windowSetShape(window* w, shape* s) {
    if(isEmpty(s)) {
        return false;
    }

    struct Node* current = s->front;
    while(current != NULL) {
        windowSetPoint(w, current->data);
        // WINDX(w,current->data.x+w->offsetX,current->data.y+w->offsetY) = current->data.c;
        current = current->next;
    }

    return true;
}

bool windowSetXY(window* w, int x, int y, char c) {
    x += w->offsetX;
    y = w->offsetY - y;
    if(x < 0 || x > w->sizeX-1) return false;
    if(y < 0 || y > w->sizeY-1) return false;
    w->buffer[y + x*w->sizeY] = c;
    return true;
}

char windowGetXY(window* w, renderpoint p) {
    p.x += w->offsetX;
    p.y += w->offsetY;
    if(p.x < 0 || p.x > w->sizeX-1) return -1;
    if(p.y < 0 || p.y > w->sizeY-1) return -1;
    return w->buffer[p.y + p.x*w->sizeY];
}

char windowGetXYraw(window* w, int x, int y) { // FIX THIS
    // printf("x:%i, y:%i, xm:%i, ym:%i\n", x, y, w->sizeX, w->sizeY);
    if(x < 0 || x > w->sizeX-1) return -1;
    if(y < 0 || y > w->sizeY-1) return -1;
    return w->buffer[y + x*w->sizeY];
}



void windowPointsToBuffer(window* w) {
    if(isEmpty(w->points)) {
        printf("points empty\n");
        return;
    }
    printf("points not empty with len of %i\n", w->points->len);

    struct Node* current = w->points->front;
    while(current != NULL) {
        WINDX(w,current->data.x,current->data.y) = current->data.c;
        current = current->next;
    }
}


void windowPrint(window* w) {
    printf("\033[%d;%dH", 0, 0);
    windowPointsToBuffer(w);  

    for(int y = 0; y < w->sizeY; y++) {
        for(int x = 0; x < w->sizeX; x++) {
            printf("%c", w->buffer[y + x*w->sizeY]);
        }
        printf("\n");
    }

    windowClear(w);

}

void windowOutline(window* w) {
    for(int i = 0; i < w->sizeX; i++) { 
        w->buffer[i*w->sizeY] = '-';
        w->buffer[w->sizeY + i*w->sizeY - 1] = '-';
    }

    for(int i = 0; i < w->sizeY; i++) {
        w->buffer[i] = '|';
        w->buffer[i + (w->sizeX-1)*w->sizeY] = '|';
    }

    w->buffer[0] = '+';
    w->buffer[w->sizeY-1] = '+';
    w->buffer[(w->sizeX-1)*w->sizeY] = '+';
    w->buffer[w->sizeX*w->sizeY - 1] = '+';
}

void windowOrigin(window* w) { WINDX(w, w->offsetX, w->offsetY) = '+';}

void windowPlotAxes(window* w) {
    for(int y = 0; y < w->sizeY; y++) {
        WINDX(w, w->offsetX, y) = '|';
    }

    for(int x = 0; x < w->sizeX; x++) {
        WINDX(w, x, w->offsetY) = '-';
    }

    WINDX(w, w->offsetX, w->offsetY) = '+';
}

void windowFree(window* w) {
    free(w->buffer);
    freeQueue(w->points);
    free(w);
}


void windowMainLoop(window* w, void (*mainFunc)()) {
    mainFunc();
}