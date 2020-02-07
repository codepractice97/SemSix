#include <graphics.h>
#include <stdio.h>

enum { TOP=0x8, BOTTOM=0x4, RIGHT=0x2, LEFT=0x1 };

int xmin,ymin,xmax,ymax,xl1,yl1,xl2,yl2;

void input(){
	printf("Enter window coordinates\n");
	printf("For top left\n");
	printf("X: ");
	scanf("%d", &xmin);
	printf("Y: ");
	scanf("%d", &ymin);
	printf("For bottom right\n");
	printf("X: ");
	scanf("%d", &xmax);
	printf("Y: ");
	scanf("%d", &ymax);
	printf("Enter line to be clipped\n");
	printf("For Point 1\n");
	printf("X: ");
	scanf("%d", &xl1);
	printf("Y: ");
	scanf("%d", &yl1);
	printf("For Point 2\n");
	printf("X: ");
	scanf("%d", &xl2);
	printf("Y: ");
	scanf("%d", &yl2);
}

int calcoutcode(int x, int y){
	int outcode = 0;
	if (x < xmin)
		outcode |= LEFT;
	else if (x > xmax)
		outcode |= RIGHT;
	if (y < ymin)
		outcode |= TOP;
	else if (y > ymax)
		outcode |= BOTTOM;
	return outcode;
}

bool doCLipping(){
	int code1 = calcoutcode(xl1,yl1);
	int code2 = calcoutcode(xl2,yl2);
	printf("outcode for point 1: %d\n", code1);
	printf("outcode for point 2: %d\n", code2);
	printf("OR: %d\n", code1 | code2);
	printf("AND: %d\n", code1 & code2);

	bool accept = false, done = false;
	do {
		if (!(code1 | code2)){ // Trivial Acceptance
			accept = true; done = true;
		} else if (code1 & code2) { // Trivial Rejection
			done = true;
		} else {
			int codeOut = code1 ? code1 : code2;
			int x,y;
			if (codeOut & TOP) { // Clip from top
				x = xl1 + (xl2-xl1)*(ymin-yl1)/(yl2-yl1);
				y = ymin;
			} else if (codeOut & BOTTOM) {
				x = xl1 + (xl2-xl1)*(ymax-yl1)/(yl2-yl1);
				y = ymax;
			} else if (codeOut & RIGHT) {
				y = yl1 + (yl2-yl1)*(xmax-xl1)/(xl2-xl1);
				x = xmax;
			} else {
				y = yl1 + (yl2-yl1)*(xmin-xl1)/(xl2-xl1);
				x = xmin;
			}

			if(codeOut == code1){
				xl1 = x; yl1 = y; code1 = calcoutcode(xl1,yl1);
			} else {
				xl2 = x; yl2 = y; code2 = calcoutcode(xl2,yl2);
			}
		}
	} while(!done);
	return accept;
}

void cohenClipping(){
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	line(xl1,yl1,xl2,yl2);
	rectangle(xmin,ymin,xmax,ymax);
	getch();
	cleardevice();
	rectangle(xmin,ymin,xmax,ymax);
	if(doCLipping())
		line(xl1,yl1,xl2,yl2);
	getch();
	closegraph();
}

int main(){
	input();
	cohenClipping();
	return 0;
}