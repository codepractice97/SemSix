#include <iostream>
#include <stdio.h>
#include <graphics.h>

#include "Drawer.h"
#include "Definitions.h"

Object create3dObject(char *obFName){
    int vCount, eCount;
    FILE *data;
    if(!(data = fopen(obFName, "r"))){
        printf("Object file not found\nProgram Terminating\n");
        exit(0);
    }

    fscanf(data, "%d\n", &vCount);
    Object object(vCount);
	for (int i = 0; i < vCount; i++){
        int x,y,z;
        fscanf(data, "%d,%d,%d\n", &x, &y, &z);
        object.vertices[i][0] = x;
        object.vertices[i][1] = y;
        object.vertices[i][2] = z;
        object.vertices[i][3] = 1;
	}

    fscanf(data, "%d\n", &eCount);
	for (int i = 0; i < eCount; i++){
        int v1,v2;
        fscanf(data, "%d,%d\n", &v1, &v2);
        object.edges[v1-1][v2-1] += 1;
	}
    return object;
}

TRANSFORMATION_TYPE transformationOpt(){
    int opt;
    std::cout << "Choose Transformation Type:" << std::endl;
    std::cout << "1: Translation" << std::endl;
    std::cout << "2: Scaling" << std::endl;
    std::cout << "3: Rotation(About X axis)" << std::endl;
    std::cout << "4: Rotation(About Y axis)" << std::endl;
    std::cout << "5: Rotation(About Z axis)" << std::endl;
    std::cout << "6: Shearing" << std::endl;
    std::cout << "7: Reflection(Through XY Plane)" << std::endl;
    std::cout << "8: Reflection(Through YZ Plane)" << std::endl;
    std::cout << "9: Reflection(Through XZ Plane)" << std::endl;
    std::cout << "Any other value: No Transformation" << std::endl;
    scanf("%d", &opt);
    switch (opt) {
        case 1: return TRANSLATION;
        case 2: return SCALING;
        case 3: return ROTATION_X;
        case 4: return ROTATION_Y;
        case 5: return ROTATION_Z;
        case 6: return SHEARING;
        case 7: return REFLECTION_XY;
        case 8: return REFLECTION_YZ;
        case 9: return REFLECTION_XZ;
        default: return NO_TRANS;
    }
}

PROJECTION_TYPE projectionOpt(){
    int opt;
    std::cout << "Choose Projection Type:" << std::endl;
    std::cout << "1: Orthographic" << std::endl;
    std::cout << "2: Axonometric(Isometric)" << std::endl;
    std::cout << "3: Oblique" << std::endl;
    std::cout << "4: Perspective" << std::endl;
    std::cout << "Any other value: Orthographic" << std::endl;
    scanf("%d", &opt);
    switch (opt) {
        case 1: return ORTHOGRAPHIC;
        case 2: return AXONOMETRIC;
        case 3: return OBLIQUE;
        case 4: return PERSPECTIVE;
        default: return ORTHOGRAPHIC;
    }
}

int main(int argc, char **argv){
    char *objectFileName;
    if (argc >= 2)
        objectFileName = argv[1];
    else {
        printf("Object file not provided\n");
        exit(0);
    }

    Object object = create3dObject(objectFileName);

    PROJECTION_TYPE ptype = projectionOpt();
    int px, py, pz;
    if (ptype == PERSPECTIVE){
        std::cout << "Enter Perspective point(x,y,z)\n";
        scanf("%d,%d,%d", &px, &py, &pz);
    }

    Transformer transformer(transformationOpt());
    transformer.displayTranformationMatrix();
    Drawer drawer(px, py, pz);
    setcolor(WHITE);
    drawer.drawObject(object, ptype);
    Object transformedObject = transformer.transform(object);
    setcolor(RED);
    drawer.drawObject(transformedObject, ptype);

    return 0;
}