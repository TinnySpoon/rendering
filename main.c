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
renderpointfl rotationPoint;
float theta;

void mainFunc(window* w) {
	windowPrint(w);
	moveCursorTo(0,0);

	if(ballY < -40)
		ballDY = 1;
	else if (ballY > 40)
		ballDY = -1;
	
	ballY += ballDY;
	
	printf("\033[1mmain p1.x %f\n", p1.x);
	printf("main p1.y %f\n", p1.y);

	renderpointfl triangleCenter = newrpfl(ballY, ballY, '.');
	shape* l = line(triangleCenter, rptorpfl(p2));
	printf("Line length %i\n", l->len);
	shape* tri = eqtriangle(triangleCenter, ballY, theta);

	windowOutline(w);
	windowPlotAxes(w);
	windowSetPointCompress(w, p2);
	// windowPushPointCompress(w, rpfltorp(rp1));
	windowSetShapeCompress(w, l);
	windowSetShapeCompress(w, tri);

	theta += .05;
	theta = constrain_angle(theta);

	printf("theta = %f\n", theta);
	// printf("x = %f\n", rp1.x);
	// printf("y = %f\n", rp1.y);
	printf("cos(theta) = %f\n", cos(theta));
	printf("sin(theta) = %f\n", sin(theta));
	printf("window width = %i\n", w->sizeX);
}


int main(int argc, char** argv) {
	window* w = newWindowFixedSize();
	theta = 0;
	p1 = newrpfl(5, 20, 'O');
	p2 = newrp(-70, 0, '0');
	rotationPoint = newrpfl(5, 5, '0');
	// window* w = newWindow(atoi(argv[1]), atoi(argv[2]));
	windowMainLoop(w, mainFunc);
	return 0;
}
