#include <stdlib.h>
#include "mesh.h"


float rnd() {
	return 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
}


void insertModel(Mesh **list, std::string name, int nv, float * vArr, int nt, int * tArr, float scale) {
	Mesh * mesh = (Mesh *) malloc(sizeof(Mesh));
    mesh->name = name;
    mesh->scale = {1, 1, 1};
    mesh->rotation = {0, 0, 0};
    mesh->translation = {0, 0, 0};
	mesh->nv = nv;
	mesh->nt = nt;	
	mesh->vertices = (Vector *) malloc(nv * sizeof(Vector));
	mesh->vnorms = (Vector *)malloc(nv * sizeof(Vector));
	mesh->triangles = (Triangle *) malloc(nt * sizeof(Triangle));
	
    
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
	
    Vector* tNorms = (Vector *)malloc(nt * sizeof(Vector));
    
    ///We start by calulating all triangle normals
    for(int i = 0; i < nt; i++)
    {
        Vector a = Subtract(mesh->vertices[mesh->triangles[i].vInds[1]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        Vector b = Subtract(mesh->vertices[mesh->triangles[i].vInds[2]], mesh->vertices[mesh->triangles[i].vInds[0]]);
        tNorms[i] = Normalize(CrossProduct(a, b));
    }
    
	for (int i = 0; i < nv; i++)
    {
        Vector sum;
        int nTrigForVer = 0;
        
        for(int j = 0; j < nt; j++) ///loo thru all the triangles and check if one of thir corners is our vertex.
        {
            if ( (mesh->triangles[j].vInds[0] == i) || (mesh->triangles[j].vInds[1] == i) || (mesh->triangles[j].vInds[2] == i) )
            {
                sum = Add(sum, tNorms[j]); ///Sum the normals of all connected triangles
                nTrigForVer++;
            }
        }
        
        sum.x /= float(nTrigForVer);
        sum.y /= float(nTrigForVer);
        sum.z /= float(nTrigForVer);
        mesh->vnorms[i] = Normalize(sum);

	}
    
    ///now that we are done with the vertex normals we free the triangle normals since we don't need them
    free(tNorms);
    
	mesh->next = *list;
	*list = mesh;	
}
