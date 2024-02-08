#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>
#include "renderwindow.h"
// #include "../cm_math/cm_math.h"

#define moveCursorTo(x,y) printf("\033[%d;%dH", x, y)

int main(int argc, char** argv) {
	window* w = newWindow(150, 31);


	int frame = 0;
	
	renderpoint p1 = newrp(-50,-7, '0');
	renderpoint p2 = newrp(50,7, '0');
	shape* rect = rect2(p1, p2);
	windowSetShape(w, rect);
	windowOutline(w);
	windowPrint(w);

	printf("\n%i\n", rect->len);
	
	
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