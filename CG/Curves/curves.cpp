#include <iostream>
#include <stdio.h>
#include <graphics.h>

int xCoords[4];
int yCoords[4];

class Drawer{

    int oX, oY;

public:

    Drawer(){
        int gd = DETECT, gm;
        initgraph(&gd, &gm, NULL);
    
        oX = getmaxx() / 2;
		oY = getmaxy() / 2;
        setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
		setcolor(WHITE);
        line(0, oY, getmaxx(), oY);
        line(oX, 0, oX, getmaxy());
        setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    }

    void drawPixel(int x, int y){
        x = x + oX;
        y = (-1 * y) + oY;
        putpixel(x, y, WHITE);
    }

    ~Drawer(){
        closegraph();
    }
};

int Bezier(float t,int w[]){
    float t2 = t * t;
    float t3 = t2 * t;
    float mt = 1-t;
    float mt2 = mt * mt;
    float mt3 = mt2 * mt;
    return int(w[0]*mt3 + 3*w[1]*mt2*t + 3*w[2]*mt*t2 + w[3]*t3);
}

void drawBezier(){
    Drawer drawer;
    float step = 1.0f/std::max(getmaxx(),getmaxy());
    for(float t = 0; t <= 1; t += step)
        drawer.drawPixel(Bezier(t,xCoords),Bezier(t,yCoords));
    getch();
}

int Hermite(float t, int w[]){
    float t2 = t*t;
    float t3 = t2*t;
    return (
        (2*t3 - 3*t2 + 1)*w[0] +
        (-2*t3 + 3*t2)*w[3] +
        (t3 - 2*t2 + t)*w[1] +
        (t3 - t2)*w[2]
    );
}

void drawHermite(){
    Drawer drawer;
    float step = 1.0f/std::max(getmaxx(),getmaxy());
    for(float t = 0; t <= 1; t += step)
        drawer.drawPixel(Hermite(t,xCoords),Hermite(t,yCoords));
    getch();
}

void run(){
    printf("%s","Choose Curve Type:\n");
    printf("%s","1. Bezier\n");
    printf("%s","2. Hermite\n");
    int opt;
    scanf("%d",&opt);
    if (opt != 1 && opt != 2) exit(0);

    printf("%s","Enter two endpoints(x,y)\n");
    scanf("\n(%d,%d)",&xCoords[0],&yCoords[0]);
    scanf("\n(%d,%d)",&xCoords[3],&yCoords[3]);
    if (opt == 1){
        printf("%s","Enter two control points(x,y)\n");
        scanf("\n(%d,%d)",&xCoords[1],&yCoords[1]);
        scanf("\n(%d,%d)",&xCoords[2],&yCoords[2]);
        drawBezier();
    } else {
        printf("%s","Enter two control points(x,y)\n");
        scanf("\n(%d,%d)",&xCoords[1],&yCoords[1]);
        scanf("\n(%d,%d)",&xCoords[2],&yCoords[2]);
        drawHermite();
    }
}

int main(){
    run();

    return 0;
}