#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <math.h>
#include <stdio.h>
#include <iostream>

#include "Definitions.h"

class Transformer {

    float T [4][4];

    void setTransformationMatrix(TRANSFORMATION_TYPE t_type, float *deg = NULL){
        for(int i = 0 ; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if (i == j) T[i][i] = 1;
                else T[i][j] = 0;
            }
        }
        const double PI = atan(1) * 4;
        
        switch (t_type) {
            case TRANSLATION:
                std::cout << "Enter x, y and z values for translation" << std::endl;
                std::cin >> T[3][0];
                std::cin >> T[3][1];
                std::cin >> T[3][2];
                break;
            case SCALING:
                std::cout << "Enter x and y values" << std::endl;
                std::cin >> T[0][0];
                std::cin >> T[1][1];
                break;
            case ROTATION_X:
                if (deg == NULL){
                    std::cout << "Enter Rotation degree along x axis" << std::endl;
                    scanf("%f", deg);
                }
                T[1][1] = T[2][2] = cos(*deg * PI/180);
                T[1][2] = sin(*deg * PI/180);
                T[2][1] = -1 * T[1][2];
                break;
            case ROTATION_Y:
                if (deg == NULL){
                    std::cout << "Enter Rotation degree along y axis" << std::endl;
                    scanf("%f", deg);
                }
                T[0][0] = T[2][2] = cos(*deg * PI/180);
                T[0][2] = -1 * sin(*deg * PI/180);
                T[2][0] = -1 * T[0][2];
                break;
            case ROTATION_Z:
                if (deg == NULL){
                    std::cout << "Enter Rotation degree along z axis" << std::endl;
                    scanf("%f", deg);
                }
                T[0][0] = T[1][1] = cos(*deg * PI/180);
                T[0][1] = sin(*deg * PI/180);
                T[1][0] = -1 * T[0][1];
                break;
            case SHEARING:
                T[0][0] = -1;
                break;
            case REFLECTION_XY:
                T[0][0] = T[1][1] = -1;
                break;
            case REFLECTION_YZ:
                T[0][0] = T[1][1] = 0;
                T[0][1] = T[1][0] = 1;
                break;
            case REFLECTION_XZ:
                T[0][0] = T[1][1] = 0;
                T[0][1] = T[1][0] = -1;
                break;
        }
    }

    void displayTranformationMatrix(){
        printf("Tranformation matrix(4X4):\n");
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++)
                printf("%f ", T[i][j]);
            printf("\n");
        }
    }

public:

    Transformer(TRANSFORMATION_TYPE t_type){
        setTransformationMatrix(t_type);
    }

    Transformer(TRANSFORMATION_TYPE t_type, float deg){
        setTransformationMatrix(t_type, &deg);
    }

    void transform(Object object){
        float mul[object.vCount][4];
        for (int i = 0; i < object.vCount; i++){
            for (int j = 0; j < 4; j++){
                mul[i][j] = 0;
                for (int k = 0; k < 4; k++){
                    mul[i][j] += object.vertices[i][k] * T[k][j];
                }
            }
        }
        // copy matrix
        for (int i = 0; i < object.vCount; i++){
            for (int j = 0; j < 4; j++)
                object.vertices[i][j] = mul[i][j];
        }
        // Project back to 3D space
        for (int i = 0; i < object.vCount; i++){
            for (int j = 0; j < 4; j++){
                object.vertices[i][j] /= object.vertices[i][3];
            }
        }
    }

};

#endif