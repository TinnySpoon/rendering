#include <stdio.h>
#include "renderwindow.h"

#define moveCursorTo(x,y) printf("\033[%d;%dH", x, y)

#ifndef M_PI // vscode error checking was throwing a fit
const M_PI = 3.14;
#endif

int ballY = 0;
int ballDY = -1;
renderpointfl p1;
renderpoint p2;
float theta;

void mainFunc(window* w) {
	windowPrint(w);
	moveCursorTo(0,0);

	if(ballY < -15)
		ballDY = 1;
	else if (ballY > 15)
		ballDY = -1;
	
	ballY += ballDY;
	
	printf("main p1.x %f\n", p1.x);
	printf("main p1.y %f\n", p1.y);

	renderpointfl rp1 = renderpointflRotate(p1, RPFL0, theta);

	shape* l = line(rpfltorp(rp1), p2);
	// windowSetPoint(w, p1);
	windowSetPoint(w, p2);
	windowPushPoint(w, rpfltorp(rp1));
	windowSetShape(w, l);
	windowOutline(w);
	windowPlotAxes(w);

	theta += .1;
	theta = constrain_angle(theta);

	printf("theta = %f\n", theta);
	printf("x = %f\n", rp1.x);
	printf("y = %f\n", rp1.y);
	printf("cos(theta) = %f\n", cos(theta));
	printf("sin(theta) = %f\n", sin(theta));
}


int main(int argc, char** argv) {
	window* w = newWindowFixedSize();
	theta = 0;
	p1 = newrpfl(0, -25, 'O');
	p2 = newrp(-70, 0, '0');
	// window* w = newWindow(atoi(argv[1]), atoi(argv[2]));
	windowMainLoop(w, mainFunc);
	return 0;
}
