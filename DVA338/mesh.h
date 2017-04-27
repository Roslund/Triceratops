#ifndef _MESH_H_
#define _MESH_H_

#include "algebra.h"
#include <string>

typedef struct _Triangle {
    int vInds[3]; //vertex indices
} Triangle;

typedef struct _VertexNormalPair {
    int vertex;
    int normal;
} VertexNormalPair;


typedef struct _Mesh {
    std::string name;
    Vector scale;
    HomVector Quaternion;
    Vector translation;
    int nv;
    Vector *vertices;
    Vector *vnorms;
    int nt;
    Triangle *triangles;
    Vector *tnorms;
    Vector boundingsphereMidpoint;
    float boundingsphereRadious;
    bool visible;
    struct _Mesh *next;
    
    unsigned int vbo, ibo, vao; // OpenGL handles for rendering
} Mesh;

typedef struct _Camera {
    Vector position;
    Vector rotation;
    double fov;
    double nearPlane;
    double farPlane;
} Camera;

void insertModel(Mesh ** objlist, std::string name, int nv, float * vArr, int nt, int * tArr, float scale = 1.0);
bool loadModelFromFile(Mesh **list, std::string name, std::string path);
void calculateBoundingSphere(Mesh* mesh);
void calculateBoundingSphereFutheresPoints(Mesh* mesh);
void viewFrustrumCulling(Matrix* VW, Mesh* mesh);

#endif
