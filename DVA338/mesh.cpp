#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"
#include <vector>
#include <random>
#include "algebra.h"

// Random seed
std::random_device rd;

// Initialize Mersenne Twister pseudo-random number generator
std::mt19937 gen(rd());

float rnd(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return static_cast <float>(dis(gen));
}

void insertModel(Mesh **list, std::string name, int nv, float * vArr, int nt, int * tArr, float scale) {
    Mesh * mesh = (Mesh *) malloc(sizeof(Mesh));
    mesh->name = name;
    mesh->scale = {1, 1, 1};
    mesh->Quaternion = {0, 0, 0, 0};
    //mesh->translation = {rnd(-50, 50), rnd(-50, 50), -rnd(0, 100)};
    mesh->translation = {0, 0, 0};
    mesh->nv = nv;
    mesh->nt = nt;
    mesh->vertices = (Vector *) malloc(nv * sizeof(Vector));
    mesh->vnorms = (Vector *)malloc(nv * sizeof(Vector));
    mesh->triangles = (Triangle *) malloc(nt * sizeof(Triangle));
    mesh->tnorms = (Vector *) malloc(nt * sizeof(Vector));
    mesh->visible = true;
    
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
                mesh->vnorms[i] = Add(mesh->vnorms[i], mesh->tnorms[j]);
            }
        }
        mesh->vnorms[i] = Normalize(mesh->vnorms[i]);
    }
    
    //Add it first in the mesh list
    mesh->next = *list;
    *list = mesh;
}

bool loadModelFromFile(Mesh **list, std::string name, std::string path) {

    std::vector< unsigned int > uvIndices;
    std::vector< unsigned int > normalIndices;
    std::vector< Vector > temp_vertices;
    std::vector< Triangle > temp_triangles;
    std::vector< Vector > temp_normals;
    std::vector< VertexNormalPair > vnPairs;
    
    path = "/Users/enari/Desktop/" + path;
    
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
        if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            Vector normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            //std::string vertex1, vertex2, vertex3;
            int uvIndex[4];
            int normalIndex[4];
            int vertexIndex[4];
            bool four = false;
            
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches == 1)
            {
                matches = fscanf(file, "%d %d\n", &vertexIndex[1], &vertexIndex[2]);
                if(matches == 0)
                {
                    matches = fscanf(file, "/%d %d//%d %d//%d\n", &normalIndex[0], &vertexIndex[1], &normalIndex[1], & vertexIndex[2], &normalIndex[2] );
                }
                else if(matches != 2)
                {
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
            }
            else if(matches == 2)
            {
                matches = fscanf(file, "%d/%d %d/%d %d/%d", &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2], &vertexIndex[3], &uvIndex[3] );
                if(matches == 6)
                    four = true;
            }
            else
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            
            //Add our vetexindexes to a triangle and add that to the vector
            //Note that OBJ indexes strats att 1 not 0, therefor -1
            Triangle triangle = {vertexIndex[0]-1, vertexIndex[1]-1, vertexIndex[2]-1};
            temp_triangles.push_back(triangle);
            if(four)
            {
                triangle = {vertexIndex[1]-1, vertexIndex[2]-1, vertexIndex[3]-1};
                temp_triangles.push_back(triangle);
                triangle = {vertexIndex[3]-1, vertexIndex[0]-1, vertexIndex[1]-1};
                temp_triangles.push_back(triangle);
            }
            VertexNormalPair one = {vertexIndex[0]-1, normalIndex[0]-1};
            VertexNormalPair two = {vertexIndex[1]-1, normalIndex[1]-1};
            VertexNormalPair three = {vertexIndex[2]-1, normalIndex[2]-1};
            vnPairs.push_back(one);
            vnPairs.push_back(two);
            vnPairs.push_back(three);
            
            
        }
    }
    
    Mesh* mesh = (Mesh *) malloc(sizeof(Mesh));;
    mesh->name = name;
    mesh->scale = {1, 1, 1};
    mesh->Quaternion = {0, 0, 0, 0};
    mesh->translation = {0, 0, 0};
    mesh->nv = (int)temp_vertices.size();
    mesh->nt = (int)temp_triangles.size();
    mesh->vertices = (Vector *) malloc(mesh->nv * sizeof(Vector));
    mesh->vertices = temp_vertices.data();
    mesh->vnorms = (Vector *)malloc(mesh->nv * sizeof(Vector));
    mesh->triangles = (Triangle *) malloc(mesh->nt * sizeof(Triangle));
    mesh->triangles = temp_triangles.data();
    mesh->tnorms = (Vector *) malloc(mesh->nt * sizeof(Vector));
    mesh->visible = true;
    
    
    if(temp_normals.size() == 0)
    {
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
                    mesh->vnorms[i] = Add(mesh->vnorms[i], mesh->tnorms[j]);
                }
            }
            //mesh->vnorms[i] = Normalize(mesh->vnorms[i]);
        }
    }
    else{
        for(auto const &a : vnPairs)
        {
            mesh->vnorms[a.vertex] = temp_normals[a.normal];
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

//VW is the combined model view perspective matrix
void viewFrustrumCulling(Matrix* VW, Mesh* mesh)
{
    Vector c = mesh->boundingsphereMidpoint;
    float radious = mesh->boundingsphereRadious *2;
    HomVector center = {c.x, c.y, c.z, 1};
    HomVector left =    {VW->e[3]-VW->e[0], VW->e[7]-VW->e[4], VW->e[11]-VW->e[8], VW->e[15]-VW->e[12]};
    HomVector right =   {VW->e[3]+VW->e[0], VW->e[7]+VW->e[4], VW->e[11]+VW->e[8], VW->e[15]+VW->e[12]};
    HomVector bottom =  {VW->e[3]-VW->e[1], VW->e[7]-VW->e[5], VW->e[11]-VW->e[9], VW->e[15]-VW->e[13]};
    HomVector top =     {VW->e[3]+VW->e[1], VW->e[7]+VW->e[5], VW->e[11]+VW->e[9], VW->e[15]+VW->e[13]};
    HomVector near =    {VW->e[3]-VW->e[2], VW->e[7]-VW->e[6], VW->e[11]-VW->e[10], VW->e[15]-VW->e[14]};
    HomVector far =     {VW->e[3]+VW->e[2], VW->e[7]+VW->e[6], VW->e[11]+VW->e[10], VW->e[15]+VW->e[14]};
    NormalizePlane(left);
    NormalizePlane(right);
    NormalizePlane(bottom);
    NormalizePlane(top);
    NormalizePlane(near);
    NormalizePlane(far);
    
    if(DotProduct(left, center) <= -radious)
    {
        //printf("Outside Left\n");
    }
    else if(DotProduct(right, center) <= -radious)
    {
        //printf("Outside Right\n");
    }
    else if(DotProduct(bottom, center) <= -radious)
    {
        //printf("Outside Bottom\n");
    }
    else if(DotProduct(top, center) <= -radious)
    {
        //printf("Outside Top\n");
    }
    else if(DotProduct(near, center) <= -radious)
    {
        //printf("Outside Near\n");
    }
    else if(DotProduct(far, center) <= -radious)
    {
        //printf("Outside Far\n");
    }
    else
    {
        //printf("Inside\n");
        mesh->visible = true;
        return;
    }
    mesh->visible = false;
}
