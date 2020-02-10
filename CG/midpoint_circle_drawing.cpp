#include <stdio.h>

int x1, y1, r;

void input(){
    printf("Enter center point of circle\n");
    printf("X: ");
    scanf("%d", &x1);
    printf("y: ");
    scanf("%d", &y1);
    printf("Enter radius of circle: ");
    scanf("%d", &r);
}

void writeCirclePoints(int x, int y){
    printf("(%d, %d)", x+x1, y+y1);
    printf("(%d, %d)", -x+x1, y+y1);
    printf("(%d, %d)", -x+x1, -y+y1);
    printf("(%d, %d)", x+x1, -y+y1);
    if (x!=y){
        printf("(%d, %d)", y+y1, x+x1);
        printf("(%d, %d)", y+y1, -x+x1);
        printf("(%d, %d)", -y+y1, -x+x1);
        printf("(%d, %d)", -y+y1, x+x1);
    }
}

void drawmidpointcircle(){
    int d = 1 - r;
    int x = 0, y = r;

    writeCirclePoints(x,y);

    while(x<y){
        if (d < 0){ // Select E
            d += 2 * x + 3;
            x++;
        } else {   // Select SE
            d += 2 * (x - y) + 5;
            x++; y--;
        }
        printf("D: %d", d);
        writeCirclePoints(x,y);
    }
}

int main(){
    input();
    drawmidpointcircle();
    return 0;
}