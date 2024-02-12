#include <stdio.h>
#include "renderwindow.h"

#define moveCursorTo(x,y) printf("\033[%d;%dH", x, y)

#ifndef M_PI // vscode error checking was throwing a fit
const M_PI = 3.14;
#endif

int ballY = 0;
int ballDY = -1;

void mainFunc(window* w) {
	if(ballY < -10)
		ballDY = 1;
	else if (ballY > 10)
		ballDY = -1;
	
	ballY += ballDY;
	
	renderpoint p1 = newrp(0, ballY, 'O');
	windowSetPoint(w, p1);
	windowOutline(w);
	windowPrint(w);
}


int main(int argc, char** argv) {
	// window* w = newWindowFixedSize();
	window* w = newWindow(atoi(argv[1]), atoi(argv[2]));
	windowMainLoop(w, mainFunc);
	return 0;
}
