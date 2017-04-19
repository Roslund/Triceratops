#include <stdlib.h>
#include "mesh.h"


void insertModel(Mesh **list, std::string name, int nv, float * vArr, int nt, int * tArr, float scale) {
    Mesh * mesh = (Mesh *) malloc(sizeof(Mesh));
    mesh->name = name;
    mesh->scale = {1, 1, 1};
    mesh->Quaternion = {0, 0, 0, 0};
    mesh->translation = {0, 0, 0};
    mesh->nv = nv;
    mesh->nt = nt;
    mesh->vertices = (Vector *) malloc(nv * sizeof(Vector));
    mesh->vnorms = (Vector *)malloc(nv * sizeof(Vector));
    mesh->triangles = (Triangle *) malloc(nt * sizeof(Triangle));
    mesh->tnorms = (Vector *) malloc(nt * sizeof(Vector));
    
    // set mesh vertices
    for (int i = 0; i < nv; i++) {
        mesh->vertices[i].x = vArr[i*3] * scale;
        mesh->vertices[i].y = vArr[i*3+1] * scale;
        mesh->vertices[i].z = vArr[i*3+2] * scale;
    }
    
    // set mesh triangles
    for (int i = 0; i < nt; i++) {
        mesh->triangles[i].vInds[0] = tArr[i*3];
        mesh->triangles[i].vInds[1] = tArr[i*3+1];
        mesh->triangles[i].vInds[2] = tArr[i*3+2];
    }
    
    // Assignment 1:
    // Calculate and store suitable vertex normals for the mesh here.

    /// Calulating triangle normals
    for(int i = 0; i < nt; i++) {
        Vector a = Subtract(mesh->vertices[mesh->triangles[i].vInds[1]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        Vector b = Subtract(mesh->vertices[mesh->triangles[i].vInds[2]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        mesh->tnorms[i] = Normalize(CrossProduct(a, b));
    }
    
    // Calculate vetex normals
    for (int i = 0; i < nv; i++) {
        for(int j = 0; j < nt; j++) {
            if ( (mesh->triangles[j].vInds[0] == i) || (mesh->triangles[j].vInds[1] == i) || (mesh->triangles[j].vInds[2] == i) ) {
                mesh->vnorms[i] = Normalize(Add(mesh->vnorms[i], mesh->tnorms[j]));
            }
        }
    }
    
    //Add it first in the mesh list
    mesh->next = *list;
    *list = mesh;
}

void calculateBoundingSphere(Mesh* mesh)
{
    Vector min = mesh->vertices[0];
    Vector max = mesh->vertices[0];
    
    for (int i = 0; i < mesh->nv; i++)
    {
        if(mesh->vertices[i].x < min.x)
            min.x = mesh->vertices[i].x;
        if(mesh->vertices[i].x > max.x)
            max.x = mesh->vertices[i].x;
        
        if(mesh->vertices[i].y < min.y)
            min.y = mesh->vertices[i].y;
        if(mesh->vertices[i].y > max.y)
            max.y = mesh->vertices[i].y;
        
        if(mesh->vertices[i].z < min.z)
            min.z = mesh->vertices[i].z;
        if(mesh->vertices[i].z > max.z)
            max.z = mesh->vertices[i].z;
    }
    
    Vector minToMax = Subtract(max, min);
    mesh->boundingsphereRadious = Length(minToMax)/2.f;
    
    mesh->boundingsphereMidpoint.x = min.x + (minToMax.x/2.f);
    mesh->boundingsphereMidpoint.y = min.y + (minToMax.y/2.f);
    mesh->boundingsphereMidpoint.z = min.z + (minToMax.z/2.f);
}
