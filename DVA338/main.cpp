//#define _CRT_SECURE_NO_WARNINGS
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "algebra.h"
#include "shaders.h"
#include "mesh.h"
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>


int screen_width = 1024;
int screen_height = 768;

Mesh *meshList = NULL; // Global pointer to linked list of triangle meshes

Camera cam = {{0,0,20}, {0,0,0}, 60, 1, 10000}; // Setup the global camera parameters

GLuint shprg; // Shader program id


// Global transform matrices
// V is the view transform
// P is the projection transform
// PV = P * V is the combined view-projection transform
Matrix V, P, PV;


void prepareShaderProgram(const char ** vs_src, const char ** fs_src) {
	GLint success = GL_FALSE;

	shprg = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_src, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) printf("Error in vertex shader!\n");
	else printf("Vertex shader compiled successfully!\n");

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_src, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) printf("Error in fragment shader!\n");
	else printf("Fragment shader compiled successfully!\n");

	glAttachShader(shprg, vs);
	glAttachShader(shprg, fs);
	glLinkProgram(shprg);
	GLint isLinked = GL_FALSE;
	glGetProgramiv(shprg, GL_LINK_STATUS, &isLinked);
	if (!isLinked) printf("Link error in shader program!\n");
	else printf("Shader program linked successfully!\n");
}

void prepareMesh(Mesh *mesh) {
	int sizeVerts = mesh->nv * 3 * sizeof(float);
	int sizeCols  = mesh->nv * 3 * sizeof(float);
	int sizeTris = mesh->nt * 3 * sizeof(int);
	
	// For storage of state and other buffer objects needed for vertex specification
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

	// Allocate VBO and load mesh data (vertices and normals)
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeVerts + sizeCols, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVerts, (void *)mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts, sizeCols, (void *)mesh->vnorms);

	// Allocate index buffer and load mesh indices
	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeTris, (void *)mesh->triangles, GL_STATIC_DRAW);

	// Define the format of the vertex data
	GLint vPos = glGetAttribLocation(shprg, "vPos");
	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Define the format of the vertex data 
	GLint vNorm = glGetAttribLocation(shprg, "vNorm");
	glEnableVertexAttribArray(vNorm);
	glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 0, (void *)(mesh->nv * 3 *sizeof(float)));

    glBindVertexArray(0);
}

void renderMesh(Mesh *mesh) {
	
	// Assignment 1: Apply the transforms from local mesh coordinates to world coordinates here
	// Combine it with the viewing transform that is passed to the shader below

    
	// Pass the viewing transform to the shader
	GLint loc_PV = glGetUniformLocation(shprg, "PV");
	glUniformMatrix4fv(loc_PV, 1, GL_FALSE, PV.e);


	// Select current resources
    glBindVertexArray(mesh->vao);
	
	// To accomplish wireframe rendering (can be removed to get filled triangles)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    
	// Draw all triangles
	glDrawElements(GL_TRIANGLES, mesh->nt * 3, GL_UNSIGNED_INT, NULL);
    
    glBindVertexArray(0);
}


void display(void) {
	Mesh *mesh;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// Assignment 1: Calculate the transform to view coordinates yourself
    V = translate(-cam.position.x, -cam.position.y, -cam.position.z);
    V = MatMatMul(rotationX(-cam.rotation.x), V);
    V = MatMatMul(rotationY(-cam.rotation.y), V);
    V = MatMatMul(rotationZ(-cam.rotation.z), V);
    
	// Assignment 1: Calculate the projection transform yourself 	
	// The matrix P should be calculated from camera parameters
	// Therefore, you need to replace this hard-coded transform. 	
	P.e[0] = 1.299038f; P.e[4] = 0.000000f; P.e[ 8] =  0.000000f; P.e[12] =  0.0f;
	P.e[1] = 0.000000f; P.e[5] = 1.732051f; P.e[ 9] =  0.000000f; P.e[13] =  0.0f;
	P.e[2] = 0.000000f; P.e[6] = 0.000000f; P.e[10] = -1.000200f; P.e[14] = -2.000200f;
	P.e[3] = 0.000000f; P.e[7] = 0.000000f; P.e[11] = -1.000000f; P.e[15] =  0.0f;

	// This finds the combined view-projection matrix
	PV = MatMatMul(P, V);

	// Select the shader program to be used during rendering
	glUseProgram(shprg);

	// Render all meshes in the scene
	mesh = meshList;
		
	while (mesh != NULL) {
		renderMesh(mesh);
		mesh = mesh->next;
	}

	glFlush();
}

void changeSize(int w, int h) {
	screen_width = w;
	screen_height = h;
	glViewport(0, 0, screen_width, screen_height);

}

void keypress(unsigned char key, int x, int y) {
	switch(key) {
    case 'x':
        cam.position.x -= 0.2f;
        break;
    case 'X':
        cam.position.x += 0.2f;
        break;
    case 'y':
        cam.position.y -= 0.2f;
        break;
    case 'Y':
        cam.position.y += 0.2f;
        break;
    case 'z':
        cam.position.z -= 0.2f;
        break;
    case 'Z':
        cam.position.z += 0.2f;
        break;
    case 'i':
        cam.rotation.x -= 0.2f;
        break;
    case 'I':
        cam.rotation.x += 0.2f;
        break;
    case 'j':
        cam.rotation.y -= 0.2f;
        break;
    case 'J':
        cam.rotation.y += 0.2f;
        break;
    case 'l':
        cam.rotation.z -= 0.2f;
        break;
    case 'L':
        cam.rotation.z += 0.2f;
        break;
	case 'Q':
	case 'q':		
		//glutLeaveMainLoop();
        //exit();
		break;
	}
    
	glutPostRedisplay();
}

void init(void) {
	// Compile and link the given shader program (vertex shader and fragment shader)
	prepareShaderProgram(vs_n2c_src, fs_ci_src); 

	// Setup OpenGL buffers for rendering of the meshes
	Mesh * mesh = meshList;
	while (mesh != NULL) {
		prepareMesh(mesh);
		mesh = mesh->next;
	}	
}

void cleanUp(void) {	
	printf("Running cleanUp function... ");
	// Free openGL resources
	// ...

	// Free meshes
	// ...
	printf("Done!\n\n");
}

// Include data for some triangle meshes (hard coded in struct variables)
#include "./models/mesh_bunny.h"
#include "./models/mesh_cow.h"
#include "./models/mesh_cube.h"
#include "./models/mesh_frog.h"
#include "./models/mesh_knot.h"
#include "./models/mesh_sphere.h"
#include "./models/mesh_teapot.h"
#include "./models/mesh_triceratops.h"


int main(int argc, char **argv) {
    
	// Setup freeGLUT	
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_3_2_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB | GLUT_3_2_CORE_PROFILE);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow("DVA338 Programming Assignments");
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keypress);

	// Output OpenGL version info
	fprintf(stdout, "OpenGL version: %s\n", (const char *)glGetString(GL_VERSION));
	fprintf(stdout, "OpenGL vendor: %s\n\n", glGetString(GL_VENDOR));
    

	// Insert the 3D models you want in your scene here in a linked list of meshes
	// Note that "meshList" is a pointer to the first mesh and new meshes are added to the front of the list	
	//insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
	insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
	//insertModel(&meshList, bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);
	//insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
	//insertModel(&meshList, frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
	//insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
	//insertModel(&meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, 12.0);
	//insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 3.0);
	
	
	init();
	glutMainLoop();

	cleanUp();	
	return 0;
}
