#ifndef DRAWER_H
#define DRAWER_H

#include <graphics.h>
#include <math.h>

#include "Definitions.h"
#include "Transformer.h"

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

    Object project(Object object, PROJECTION_TYPE p_type){
        float P[4][4];
        for(int i = 0 ; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if (i == j) P[i][i] = 1;
                else P[i][j] = 0;
            }
        }

        // Select Projection matrix
        const double PI = atan(1) * 4;
        if (p_type == ORTHOGRAPHIC) {
            P[2][2] = 0;
        } else if (p_type == AXONOMETRIC) {
            // Isometric Projection
            Transformer t1(ROTATION_Y, 45);
            object = t1.transform(object);
            Transformer t2(ROTATION_X, -35.26);
            object = t2.transform(object);
            P[2][2] = 0;
        } else if (p_type == OBLIQUE){
            P[2][0] = (1.0/2) * cos(45 * PI / 180);
            P[2][1] = (1.0/2) * sin(45 * PI / 180);
            P[2][2] = 0;
        } else if (p_type == PERSPECTIVE){
            
        }

        // Apply Projection
        Object projObject = object;
        for (int i = 0; i < projObject.vCount; i++){
            for (int j = 0; j < 4; j++){
                projObject.vertices[i][j] = 0;
                for (int k = 0; k < 4; k++){
                    projObject.vertices[i][j] += object.vertices[i][k] * P[k][j];
                }
            }
        }
        return projObject;
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

    void drawObject(Object object, PROJECTION_TYPE ptype){
        object = project(object, ptype);
        for (int i = 0; i < object.vCount; i++){
            for (int j = 0; j < object.vCount; j++){
                if (object.edges[i][j])
                    drawLine(
                        object.vertices[i][0],
                        object.vertices[i][1],
                        object.vertices[j][0],
                        object.vertices[j][1]
                    );
            }
        }
    }

    ~Drawer(){
        getchar();
        closegraph();
    }
};

#endif