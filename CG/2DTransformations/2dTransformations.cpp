#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <math.h>

float T [3][3];
int vCount = 1;

class Drawer{

    int oX, oY;
    
    void drawLine(float x1, float y1, float x2, float y2){
        y1 *= -1; y2 *= -1;
        line(
            int(x1 + oX),
            int(y1 + oY),
            int(x2 + oX),
            int(y2 + oY)
        );
    }

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

    void drawPolygon(float M[][3]){
        int p = vCount - 1;
        for (int q = 0; q < vCount; q++){
            drawLine(
                M[p][0],
                M[p][1],
                M[q][0],
                M[q][1]
            );
            p = q;
        }
    }

    ~Drawer(){
        closegraph();
    }
};

void inputTranformationMatrix(){
    std::cout << "Enter the tranformation matrix(3X3): ";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            std::cin >> T[i][j];
    }
}

void inputVertices(float M[][3]){
	for (int i = 0; i < vCount; i++){
		std::cout << "Enter vertice " << i + 1 << std::endl;
		for (int j = 0; j < 2; j++)
            std::cin >> M[i][j];
        M[i][2] = 1;
	}
}

void transform(float M[][3]){
    float mul[vCount][3];
    for (int i = 0; i < vCount; i++){
		for (int j = 0; j < 3; j++){
            mul[i][j] = 0;
            for (int k = 0; k < 3; k++){
                mul[i][j] += M[i][k] * T[k][j];
            }
        }
	}
    // copy matrix
    for (int i = 0; i < vCount; i++){
		for (int j = 0; j < 3; j++)
            M[i][j] = mul[i][j];
	}
    // Project back on h=1 plane
    for (int i = 0; i < vCount; i++){
		for (int j = 0; j < 3; j++){
            M[i][j] /= M[i][2];
        }
	}
}

void setTransformationMatrix(int opt){
    const double PI = atan(1) * 4;
    T[0][0] = T[1][1] = T[2][2] = 1;
    switch (opt) {
        case 1: // Translation
            std::cout << "Enter x and y values" << std::endl;
            std::cin >> T[2][0];
            std::cin >> T[2][1];
            break;
        case 2: // Scaling
            std::cout << "Enter x and y values" << std::endl;
            std::cin >> T[0][0];
            std::cin >> T[1][1];
            break;
        case 3: // Rotaion
            std::cout << "Enter Rotation degree" << std::endl;
            float deg;
            scanf("%f", &deg);
            T[0][0] = T[1][1] = cos(deg * PI/180);
            T[0][1] = -1 * sin(deg * PI/180);
            T[1][0] = -1 * T[0][1];
            break;
        case 4: // Shearing
            std::cout << "Enter x and y values" << std::endl;
            std::cin >> T[1][0];
            std::cin >> T[0][1];
            break;
        case 5: // Reflection against x aixs
            T[1][1] = -1;
            break;
        case 6: // Reflection against y aixs
            T[0][0] = -1;
            break;
        case 7: // Reflection against origin
            T[0][0] = T[1][1] = -1;
            break;
        case 8: // Reflection against line Y=X
            T[0][0] = T[1][1] = 0;
            T[0][1] = T[1][0] = 1;
            break;
        case 9: // Reflection against x aixs
            T[0][0] = T[1][1] = 0;
            T[0][1] = T[1][0] = -1;
            break;
        default: // User inputted Transformation matrix
            inputTranformationMatrix();
            break;
    }
}

int menuOption(){
    int opt;
    std::cout << "Choose Transformation Type:" << std::endl;
    std::cout << "1: Translation" << std::endl;
    std::cout << "2: Scaling" << std::endl;
    std::cout << "3: Rotation" << std::endl;
    std::cout << "4: Shearing" << std::endl;
    std::cout << "5: Reflection(Against X axis)" << std::endl;
    std::cout << "6: Reflection(Against Y axis)" << std::endl;
    std::cout << "7: Reflection(Against origin)" << std::endl;
    std::cout << "8: Reflection(Against line Y=X)" << std::endl;
    std::cout << "9: Reflection(Against line Y=-X)" << std::endl;
    std::cout << "Any other value: Custom transformation matrix" << std::endl;
    scanf("%d", &opt);
    return opt;
}

void run(){
    std::cout << "Enter number of vertices to enter: ";
	std::cin >> vCount;
    float M[vCount][3];
    inputVertices(M);
    
    setTransformationMatrix(menuOption());
    Drawer drawer;
    setcolor(BLUE);
    drawer.drawPolygon(M);
    transform(M);
    setcolor(RED);
    drawer.drawPolygon(M);

    getch();
}

int main(){
    run();
    return 0;
}