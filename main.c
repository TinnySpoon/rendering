#include <stdio.h>
// #include <stdlib.h>
#include "renderwindow.h"

#define moveCursorTo(x,y) printf("\033[%d;%dH", x, y)


void mainFunc() {
	printf("running mainFunc function\n");
}


int main(int argc, char** argv) {
	window* w = newWindow(150, 31);
	// window* w = 0;

	// // usleep(3000000);

	// windowMainLoop(w, mainFunc);

	// return 0;


	int frame = 0;
	
	renderpoint p1 = newrp(-50,7, '0');
	renderpoint p2 = newrp(50,4, '0');
	renderpoint p3 = newrp(40,-7, '0');
	renderpoint p4 = newrp(-40,-7, '0');
	shape* rect = rect4(p1, p2, p3, p4);
	float theta = M_PI * 3.0f / 4.0f;
	p1 = rpfltorp(renderpointflRotate(rptorpfl(p1), RPFL0, theta));
	windowPushPoint(w, p1);
	// windowPushPoint(w, p2);
	windowSetShape(w, rect);
	windowOrigin(w);
	windowPlotAxes(w);
	windowOutline(w);
	windowPrint(w);
	windowPlotAxes(w);
	windowPrint(w);

	printf("\n%f\n", theta);
	printf("\n%i\n", p1.x);
	printf("\n%i\n", p1.y);
	
	
	// for(int i = 0; i < 1000; i++) {
	// 	for(int y = 0; y < 10; y++) {
	// 		renderpoint p1 = newrp(7,y,((y)%10)+'0');
	// 		renderpoint p2 = newrp((frame%140)-70,y,((y)%10)+'0');
	// 		// windowSetXY(w, p1);
	// 		// windowSetXY(w, p2);
	// 		windowPopPoint(w);
	// 		windowPopPoint(w);

	// 		windowPushPoint(w, p1);
	// 		windowPushPoint(w, p1);
	// 		windowPushPoint(w, p2);
	// 		// windowSetXYraw(w, 1, i, (i%10)+'0');
			
	// 	}


	// 	windowOutline(w);
		

	// 	renderpoint r = newrp(0,0,'0');
	// 	windowSetXY(w, r);

	// 	frame++;
	// 	windowPrint(w);
	// 	moveCursorTo(20,20);
	// 	printf("%i", w->points->len);

	// 	usleep(16667);
	// }

	return 0;
}
