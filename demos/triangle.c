#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>

#include "../renderwindow.h"


int frame = 0;
int inputCount = 0;
void mainFunc(window* w) {

	shape* l = line(newrpfl(-40*frame, -10*frame, '0'+frame), newrpfl(40*frame, 10*frame, '0'+frame));
	windowSetShape(w, l);
	windowPrint(w);
    moveCursorTo(0,0);
    printf("testing\n");


	frame++;
	if(frame>=10) { frame=0; }

}


void *inputThread(void* threadid) {

    while(true) {
        // getch();
    }
    
    pthread_exit(NULL);
}


int main(int argc, char** argv) {
	// window* w = newWindowFixedSize();
	// windowMainLoop(w, mainFunc, 60);
    pthread_t thread;
    long t;
    pthread_create(&thread, NULL, inputThread, (void*)t);
    // printf("checking address of t:%p and thread:%p\n", &t, &thread);
    pthread_join(thread, NULL);
	return 0;
}