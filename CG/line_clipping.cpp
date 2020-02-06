#include <graphics.h>

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

void doCLipping(int code1, int code2){
	boolean accept = False, done = True;
	do {
		if (code1 | code2 == 0){ // Trivial Acceptance
			accept = True; done = True;
		} else if (code1 & code2 != 0) { // Trivial Rejection
			done = True;
		} else {
			codeOut = code1 ? code1 : code2;
			int x,y;
			if (codeOut & TOP) { // Clip from top
				x = xl1 + (xl2-xl1)*(ymax-yl0)/(yl1-yl0);
				y = ymax;
			} else if (codeOut & BOTTOM) {
				
			} else if (codeOut & RIGHT) {
				
			} else {
				
			}

			if(codeOut == code1){
				xl1 = x; yl1 = y;
			
			} else {

			}
		}
	} while(!done);
	if(accept){
		line(xl1,yl1,xl2,yl2);
	}
}

void cohenClipping(){
	int p1_outcode = calcoutcode(xl1,yl1);
	int p2_outcode = calcoutcode(xl2,yl2);
	printf("outcode for point 1: %d\n", p1_outcode);
	printf("outcode for point 2: %d\n", p2_outcode);

	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);

	doCLipping(p1_outcode ,p2_outcode );
	
	rectangle(xmin,ymin,xmax,ymax);
	delay(10000);
	closegraph();
}

int main(){
	input();
	cohenClipping();
	return 0;
}

