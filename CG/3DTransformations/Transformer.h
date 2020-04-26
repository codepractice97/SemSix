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
                std::cout << "Enter the four scaling factors" << std::endl;
                std::cin >> T[0][0];
                std::cin >> T[1][1];
                std::cin >> T[2][2];
                std::cin >> T[3][3];
                break;
            case ROTATION_X:
                if (deg == NULL){
                    deg = new float();
                    std::cout << "Enter Rotation degree along x axis" << std::endl;
                    scanf("%f", deg);
                }
                T[1][1] = T[2][2] = cos(*deg * PI/180);
                T[1][2] = sin(*deg * PI/180);
                T[2][1] = -1 * T[1][2];
                break;
            case ROTATION_Y:
                if (deg == NULL){
                    deg = new float();
                    std::cout << "Enter Rotation degree along y axis" << std::endl;
                    scanf("%f", deg);
                }
                T[0][0] = T[2][2] = cos(*deg * PI/180);
                T[0][2] = -1 * sin(*deg * PI/180);
                T[2][0] = -1 * T[0][2];
                break;
            case ROTATION_Z:
                if (deg == NULL){
                    deg = new float();
                    std::cout << "Enter Rotation degree along z axis" << std::endl;
                    scanf("%f", deg);
                }
                T[0][0] = T[1][1] = cos(*deg * PI/180);
                T[0][1] = sin(*deg * PI/180);
                T[1][0] = -1 * T[0][1];
                break;
            case SHEARING:
                std::cout << "Enter x, y and z shearing values(2 for each)" << std::endl;
                std::cin >> T[1][0];
                std::cin >> T[2][0];
                std::cin >> T[0][1];
                std::cin >> T[2][1];
                std::cin >> T[0][2];
                std::cin >> T[1][2];
                break;
            case REFLECTION_XY:
                T[2][2] = -1;
                break;
            case REFLECTION_YZ:
                T[0][0] = -1;
                break;
            case REFLECTION_XZ:
                T[1][1] = -1;
                break;
        }
    }

public:

    Transformer(TRANSFORMATION_TYPE t_type){
        setTransformationMatrix(t_type);
    }

    Transformer(TRANSFORMATION_TYPE t_type, float deg){
        setTransformationMatrix(t_type, &deg);
    }

    Object transform(Object object){
        Object transObject = object;
        for (int i = 0; i < transObject.vCount; i++){
            for (int j = 0; j < 4; j++){
                transObject.vertices[i][j] = 0;
                for (int k = 0; k < 4; k++){
                    transObject.vertices[i][j] += object.vertices[i][k] * T[k][j];
                }
            }
        }
        // Project back to 3D space
        for (int i = 0; i < transObject.vCount; i++){
            for (int j = 0; j < 4; j++){
                transObject.vertices[i][j] /= transObject.vertices[i][3];
            }
        }
        return transObject;
    }

    void displayTranformationMatrix(){
        printf("Tranformation matrix(4X4):\n");
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++)
                printf("%f ", T[i][j]);
            printf("\n");
        }
    }

};

#endif