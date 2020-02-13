#include <stdio.h>

int x1, y1, x2, y2;

void input(){
    printf("Enter two points to draw line\n");
    printf("For point 1\n");
    printf("X: ");
    scanf("%d", &x1);
    printf("y: ");
    scanf("%d", &y1);
    printf("For point 2\n");
    printf("X: ");
    scanf("%d", &x2);
    printf("y: ");
    scanf("%d", &y2);
}

void drawmidpointline(){
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = 2 * dy - dx;
    int x = x1, y = y1;
    int incr_E = 2 * dy;
    int incr_NE = 2 * (dy - dx);

    printf("(%d, %d)", x, y);

    while(x < x2){
        if (d <= 0){
            d += incr_E;
            x++;
        } else {
            d += incr_NE;
            x++; y++;
        }
        printf("(%d, %d)", x, y);
    }
}

int main(){
    input();
    drawmidpointline();
    return 0;
}