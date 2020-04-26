#ifndef DEFINITIONS_H
#define DEFINITIONS_H

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

    Object(const Object &object): Object(object.vCount) {
        std::cout << "Copied\n";
        for (int i = 0; i < vCount; i++){
            for (int j = 0; j < 4; j++)
                vertices[i][j] = object.vertices[i][j];
            for (int j = 0; j < vCount; j++)
                edges[i][j] = object.edges[i][j];
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
    REFLECTION_XZ,
    NO_TRANS
};

#endif