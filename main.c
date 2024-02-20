#include <stdio.h>
#include "renderwindow.h"


#ifndef M_PI // vscode error checking was throwing a fit
const M_PI = 3.14;
#endif

int frame = 0;
void mainFunc(window* w) {

	shape* l = line(newrpfl(-40*frame, -10*frame, '0'+frame), newrpfl(40*frame, 10*frame, '0'+frame));
	windowSetShape(w, l);
	windowPrint(w);

	frame++;
	if(frame>=10) { frame=0; }

}


int main(int argc, char** argv) {
	window* w = newWindowFixedSize();
	windowMainLoop(w, mainFunc, 60);
	// windowMainLoopGlobals(w, mainFunc, 60);
	return 0;
}