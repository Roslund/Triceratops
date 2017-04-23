#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"
#include <vector>


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

bool loadModelFromFile(Mesh **list, std::string name, std::string path) {

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< Vector > temp_vertices;
    
    FILE * file = fopen(path.c_str(), "r");
    if( file == NULL )
    {
        printf("Impossible to open the file !\n");
        return false;
    }
    
    while(true)
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            Vector vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
            {
                matches = fscanf(file, "%d %d\n", &vertexIndex[1], &vertexIndex[2]);
                if(matches != 2)
                {
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }
    }
    
    Mesh* mesh = (Mesh *) malloc(sizeof(Mesh));;
    mesh->name = name;
    mesh->scale = {1, 1, 1};
    mesh->Quaternion = {0, 0, 0, 0};
    mesh->translation = {0, 0, 0};
    mesh->nv = (int)temp_vertices.size();
    mesh->nt = (int)vertexIndices.size()/3;
    mesh->vertices = (Vector *) malloc(mesh->nv * sizeof(Vector));
    mesh->vnorms = (Vector *)malloc(mesh->nv * sizeof(Vector));
    mesh->triangles = (Triangle *) malloc(mesh->nt * sizeof(Triangle));
    mesh->tnorms = (Vector *) malloc(mesh->nt * sizeof(Vector));
    
    
    // set mesh vertices
    for (int i = 0; i < mesh->nv; i++) {
        mesh->vertices[i] = temp_vertices[i];
    }
    
    // set mesh triangles
    for (int i = 0; i < mesh->nt; i++) {
        mesh->triangles[i].vInds[0] = vertexIndices[i*3]-1;
        mesh->triangles[i].vInds[1] = vertexIndices[i*3+1]-1;
        mesh->triangles[i].vInds[2] = vertexIndices[i*3+2]-1;
    }
    
    /// Calulating triangle normals
    for(int i = 0; i < mesh->nt; i++) {
        Vector a = Subtract(mesh->vertices[mesh->triangles[i].vInds[1]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        Vector b = Subtract(mesh->vertices[mesh->triangles[i].vInds[2]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        mesh->tnorms[i] = Normalize(CrossProduct(a, b));
    }
    
    // Calculate vetex normals
    for (int i = 0; i < mesh->nv; i++) {
        for(int j = 0; j < mesh->nt; j++) {
            if ( (mesh->triangles[j].vInds[0] == i) || (mesh->triangles[j].vInds[1] == i) || (mesh->triangles[j].vInds[2] == i) ) {
                mesh->vnorms[i] = Normalize(Add(mesh->vnorms[i], mesh->tnorms[j]));
            }
        }
    }
    
    //Add it first in the mesh list
    mesh->next = *list;
    *list = mesh;
    
    return true;
    
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

//Doesent work :(
void calculateBoundingSphereFutheresPoints(Mesh* mesh)
{
    float maxLenthBetweenPoints = 0.f;
    Vector pointA;
    Vector vectorA;
    
    for (int i = 0; i < mesh->nv; i++)
    {
        float maxLengthFromV = 0.f;
        Vector pointB;
        Vector vectorB;
        for (int j = 0; j < mesh->nv; j++)
        {
            if(Length(Subtract(mesh->vertices[j], mesh->vertices[i])) > maxLengthFromV)
            {
                maxLengthFromV = Length(Subtract(mesh->vertices[j], mesh->vertices[i]));
                pointB = mesh->vertices[i];
                vectorB = Subtract(mesh->vertices[j], mesh->vertices[i]);
            }
        }
        if(maxLengthFromV > maxLenthBetweenPoints)
        {
            maxLenthBetweenPoints = maxLengthFromV;
            pointA = pointB;
            vectorA = vectorB;
        }
    }
    mesh->boundingsphereMidpoint.x = pointA.x + (vectorA.x/2.f);
    mesh->boundingsphereMidpoint.y = pointA.y + (vectorA.y/2.f);
    mesh->boundingsphereMidpoint.z = pointA.z + (vectorA.z/2.f);
    mesh->boundingsphereRadious = Length(vectorA)/2.f;
}
