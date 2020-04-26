#ifndef GRANDPARENT_H
#define GRANDPARENT_H

struct Object {
    int vCount;
    float **vertices;
    float **edges;

    Object(int vC){
        // Create vertices and edges 2D array
        vCount = vC;
        vertices = new float*[vCount];
        for(int i = 0 ; i < vCount; i++)
            vertices[i] = new float[4];
        edges = new float*[vCount];
        for(int i = 0 ; i < vCount; i++){
            edges[i] = new float[vCount];
            for(int j = 0; j < vCount; j++)
                edges[i][j] = 0;
        }
    }
};

enum PROJECTION_TYPE {
    ORTHOGRAPHIC,
    AXONOMETRIC,
    OBLIQUE,
    PERSPECTIVE
};

enum TRANSFORMATION_TYPE {
    TRANSLATION,
    SCALING,
    ROTATION_X,
    ROTATION_Y,
    ROTATION_Z,
    SHEARING,
    REFLECTION_XY,
    REFLECTION_YZ,
    REFLECTION_XZ
};

#endif