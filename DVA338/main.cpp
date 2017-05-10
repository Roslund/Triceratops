//#define _CRT_SECURE_NO_WARNINGS
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include "math.h"
#include "AntTweakBar.h"
#include "algebra.h"
#include "mesh.h"
#include <vector>

// Include data for some triangle meshes (hard coded in struct variables)
#include "./models/mesh_bunny.h"
#include "./models/mesh_cow.h"
#include "./models/mesh_cube.h"
#include "./models/mesh_frog.h"
#include "./models/mesh_knot.h"
#include "./models/mesh_sphere.h"
#include "./models/mesh_teapot.h"
#include "./models/mesh_triceratops.h"


int screen_width = 1024;
int screen_height = 768;

Mesh* meshList = NULL; // Global pointer to linked list of triangle meshes
Mesh* boundingSphere = NULL; //Global pointer to our boundingsphere mesh

Camera cam = {{0,0,20}, {0,0,0}, 60, 0.1, 10000}; // Setup the global camera parameters

Vector lightDir = {1.0f, 1.0f, 1.0f};
Vector lightDir2 = {-1.0f, 1.0f, 1.0f};
float shininess = 40;


Matrix V, P, PV;

GLuint shprg; // Shader program id

//Antons globala stuff
enum Projection {Perspective, Frustum, Ortographic};
enum Shader {Phong, modPhong, Gourad, Cartoon, Normal2Color};
enum BoundingVolume {Sphere, AABB};

Projection projection = Perspective;
Shader shader = Phong;
BoundingVolume boundingVolume = Sphere;

bool TweakBarVisible = 0;
bool drawBoundingSphere = 1;

TwBar *bar;// Pointer to a tweak bar
TwType TW_TYPE_VEC;
char loadModelName[64] = "";

// To Measure speed
int lastTime = glutGet(GLUT_ELAPSED_TIME);
int frames = 0;
float msPerFrame = 0;


void prepareShaderProgram(const char ** vs_src, const char ** fs_src) {
    GLint success = GL_FALSE;
    
    shprg = glCreateProgram();
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_src, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) printf("Error in vertex shader!\n");
    else printf("Vertex shader compiled successfully!\n");
    
    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);
        
        printf("%s", errorLog.data());
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(vs); // Don't leak the shader.
        return;
    }
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_src, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) printf("Error in fragment shader!\n");
    else printf("Fragment shader compiled successfully!\n");
    
    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);
        
        printf("%s", errorLog.data());
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fs); // Don't leak the shader.
        return;
    }
    
    
    glAttachShader(shprg, vs);
    glAttachShader(shprg, fs);
    glLinkProgram(shprg);
    GLint isLinked = GL_FALSE;
    glGetProgramiv(shprg, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        printf("Link error in shader program!\n");
        
        GLint maxLength = 0;
        glGetShaderiv(shprg, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(shprg, maxLength, &maxLength, &errorLog[0]);
        printf("%s", errorLog.data());
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shprg); // Don't leak the shader.
        return;
    }
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
    glEnable(GL_DEPTH_TEST); ///Needed to get Z-buffer/depth for assignment 1.3
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //glEnable(GL_CULL_FACE); //BACK-FACE CULLING
    //glCullFace(GL_BACK); //BACK-FACE CULLING
    
    // Assignment 1: Apply the transforms from local mesh coordinates to world coordinates here
    // Combine it with the viewing transform that is passed to the shader below
    Matrix M, PVM;

    M = MatMatMul(rotationQuaternion(mesh->Quaternion), scale(mesh->scale));
    M = MatMatMul(translate(mesh->translation), M);
    PVM = MatMatMul(PV, M);
    
    //Do the culling
    viewFrustrumCulling(&PVM, mesh);
    
    //If mesh is not visible don't render it.
    if(!mesh->visible)
        return;
    
    // Pass the viewing transform to the shader
    glUniformMatrix4fv(glGetUniformLocation(shprg, "Projection"), 1, GL_FALSE, P.e);
    glUniformMatrix4fv(glGetUniformLocation(shprg, "View"), 1, GL_FALSE, V.e);
    glUniformMatrix4fv(glGetUniformLocation(shprg, "Model"), 1, GL_FALSE, M.e);
    
    glUniform4f(glGetUniformLocation(shprg, "AmbientProduct"), 0.1f, 0.1f, 0.1f, 1.0f);
    glUniform4f(glGetUniformLocation(shprg, "DiffuseProduct"), 0.0f, 0.0f, 1.0f, 1.0f);
    glUniform4f(glGetUniformLocation(shprg, "SpecularProduct"), 1.0f, 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shprg, "LightPosition"), lightDir.x, lightDir.y, lightDir.z);
    glUniform1f(glGetUniformLocation(shprg, "Shininess"), shininess);
    
    glUniform4f(glGetUniformLocation(shprg, "AmbientProduct2"), 0.1f, 0.1f, 0.1f, 1.0f);
    glUniform4f(glGetUniformLocation(shprg, "DiffuseProduct2"), 1.0f, 0.0f, 0.0f, 1.0f);
    glUniform4f(glGetUniformLocation(shprg, "SpecularProduct2"), 1.0f, 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shprg, "LightPosition2"), lightDir2.x, lightDir2.y, lightDir2.z);
    glUniform1f(glGetUniformLocation(shprg, "Shininess"), shininess);
    
    // Select current resources
    glBindVertexArray(mesh->vao);
    
    // To accomplish wireframe rendering (can be removed to get filled triangles)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw all triangles
    glDrawElements(GL_TRIANGLES, mesh->nt * 3, GL_UNSIGNED_INT, NULL);
    
    /*if(drawBoundingSphere)
    {
        //Calculate new VW
        W = MatMatMul(translate(mesh->boundingsphereMidpoint), scale({mesh->boundingsphereRadious, mesh->boundingsphereRadious, mesh->boundingsphereRadious}));
        VW = MatMatMul(VW, W);
        
        // Select current resources
        glBindVertexArray(boundingSphere->vao);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUniformMatrix4fv(glGetUniformLocation(shprg, "PV"), 1, GL_FALSE, VW.e);
        glUniform1i(glGetUniformLocation(shprg, "White"), 1);
        glDrawElements(GL_TRIANGLES, boundingSphere->nt * 3, GL_UNSIGNED_INT, NULL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }*/
    
    // Unselect resources
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
    ///Should we relly caluclate P here? seams uneasseary to do it everytime something changes
    //This checks if we use paralell or perspective projection
    if (projection == Perspective)
    {
        P = generatePerspectiveProjectionMatrix(screen_width, screen_height, cam.nearPlane, cam.farPlane, cam.fov);
    }
    else if(projection == Frustum)
    {
        P = generateFrustumProjectionMatrix(screen_width, screen_height, cam.nearPlane, cam.farPlane, cam.fov);
    }
    else
    {
        P = generateOrthographicProjectionMatrix(screen_width, screen_height, cam.nearPlane, cam.farPlane, cam.fov);
    }
    
    // This finds the combined view-projection matrix
    PV = MatMatMul(P, V);
    
    // Select the shader program to be used during rendering
    glUseProgram(shprg);
    
    // Render all meshes in the scene
    mesh = meshList;
    
    while (mesh != NULL)
    {
        renderMesh(mesh);
        mesh = mesh->next;
    }
    
    TwDraw();
    //glFlush();
    
    // Present frame buffer
    glutSwapBuffers();
    
    // Recall Display at next frame
    glutPostRedisplay();
}

void changeSize(int w, int h) {
    screen_width = w;
    screen_height = h;
    glViewport(0, 0, screen_width, screen_height);
    
    TwWindowSize(screen_width, screen_height); /// Send the new window size to AntTweakBar
}

void keypress(unsigned char key, int x, int y) {
    matrix rotation;
    rotation = MatMatMul(rotationY(cam.rotation.y), rotationZ(cam.rotation.z));
    rotation = MatMatMul(rotationX(cam.rotation.x), rotation);
    
    TwEventKeyboardGLUT(key, x, y);
    
    switch(key) {
        case '!':
            if (TweakBarVisible) {
                TwDefine(" TweakBar visible=false ");
                TweakBarVisible = 0;
            } else {
                TwDefine(" TweakBar visible=true ");
                TweakBarVisible = 1;
            }
            break;
        case 'a': //Left
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {-0.2f, 0, 0})));
            break;
        case 'd': //right
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0.2f, 0, 0})));
            break;
        case 'w': //forward
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0, -0.2f})));
            break;
        case 's': //backwars
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0, 0.2f})));
            break;
        case 'q': //up
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, -0.2f, 0})));
            break;
        case 'e': //down
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0.2f, 0})));
            break;
        case 'A': //Left
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {-0.9f, 0, 0})));
            break;
        case 'D': //right
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0.9f, 0, 0})));
            break;
        case 'W': //forward
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0, -0.9f})));
            break;
        case 'S': //backwars
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0, 0.9f})));
            break;
        case 'Q': //up
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, -0.9f, 0})));
            break;
        case 'E': //down
            cam.position = Add(cam.position, Homogenize(MatVecMul(rotation, {0, 0.9f, 0})));
            break;
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
        case 'k': //look down
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {-0.1f, 0, 0})));
            break;
        case 'i': //look up
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0.1f, 0, 0})));
            break;
        case 'l': //look right
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, -0.1f, 0})));
            break;
        case 'j': //look left
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0.1f, 0})));
            break;
        case 'u': //rotate counterclok
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0, -0.1f})));
            break;
        case 'o': //rotate clock
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0, 0.1f})));
            break;
        case 'K': //look down
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {-0.5f, 0, 0})));
            break;
        case 'I': //look up
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0.5f, 0, 0})));
            break;
        case 'L': //look right
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, -0.5f, 0})));
            break;
        case 'J': //look left
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0.5f, 0})));
            break;
        case 'U': //rotate counterclok
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0, -0.5f})));
            break;
        case 'O': //rotate clock
            cam.rotation = Add(cam.rotation, Homogenize(MatVecMul(rotation, {0, 0, 0.5f})));
            break;
    }
    
    
    glutPostRedisplay();
}

void init(std::string vert, std::string frag) {
    // Compile and link the given shader program (vertex shader and fragment shader)
    std::ifstream f;
    std::stringstream buf;
    f.open(vert.c_str());
    buf << f.rdbuf();
    
    std::string vertShaderStr = buf.str();
    const char* vertShaderSrc = vertShaderStr.c_str();
    
    buf.str("");
    f.close();
    f.open(frag.c_str());
    buf << f.rdbuf();
    
    std::string fragShaderStr = buf.str();
    const char* fragShaderSrc = fragShaderStr.c_str();
 
    
    prepareShaderProgram(&vertShaderSrc, &fragShaderSrc);
    
    // Setup OpenGL buffers for rendering of the meshes
    Mesh * mesh = meshList;
    while (mesh != NULL) {
        prepareMesh(mesh);
        mesh = mesh->next;
    }
    
    // for bounding sphere as well;
    prepareMesh(boundingSphere);
}

void cleanUp(void) {
    printf("Running cleanUp function... ");
    // Free openGL resources
    // ...
    
    // Free meshes
    // ...
    printf("Done!\n\n");
}

void timerfunc(void) {
    // Measure speed
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    frames++;
    if (currentTime - lastTime > 1000) {
        msPerFrame = (currentTime-lastTime)/(float)frames;
        lastTime = currentTime;
        frames = 0;
    }
}

void removeModelFromTwbar(Mesh* mesh) {
    TwRemoveVar(bar, (mesh->name + "Visible").c_str());
    TwRemoveVar(bar, (mesh->name + "Rotation").c_str());
    TwRemoveVar(bar, (mesh->name + "Scale").c_str());
    TwRemoveVar(bar, (mesh->name + "Translation").c_str());
    TwRemoveVar(bar, (mesh->name + "Unload").c_str());
}

void removeMeshFromMeshlist(Mesh* meshToRemove) {
    if(meshList == meshToRemove)
        meshList = meshList->next;
    
    Mesh* mesh = meshList;
    while(mesh != NULL)
    {
        if(mesh->next == meshToRemove)
            mesh->next = meshToRemove->next;
        else
            mesh = mesh->next;
    }
}

void TW_CALL TwUnloadModel(void *clientData) {
    Mesh* mesh = (Mesh*)clientData;
    
    removeModelFromTwbar(mesh);
    removeMeshFromMeshlist(mesh);
    
    fprintf(stdout, "Unloaded  Model: %s\n\n", mesh->name.c_str());
    free(mesh);
}

int addModelToTwbar(Mesh* mesh) {
    
    //Apending numbers to modelnames to keep them uniqe
    int i = 1;
    std::string name = mesh->name;
    
    
    
    while(0 == TwAddVarRO(bar, (mesh->name + "Visible").c_str(), TW_TYPE_BOOLCPP, &mesh->visible, (" label='Visble' Group='" + mesh->name + "' true=Visible false=Culled ").c_str()))
    {
        mesh->name = (name + std::to_string(i++)).c_str();
    }
    TwAddVarRW(bar, (mesh->name + "Rotation").c_str(), TW_TYPE_QUAT4F, &mesh->Quaternion, (" label='Model Rotation' Group='" + mesh->name + "' opened=false ").c_str());
    TwAddVarRW(bar, (mesh->name + "Scale").c_str(), TW_TYPE_VEC, &mesh->scale, (" label='Model Scale' Group='" + mesh->name + "' opened=false ").c_str());
    TwAddVarRW(bar, (mesh->name + "Translation").c_str(), TW_TYPE_VEC, &mesh->translation, (" label='Model Translation' Group='" + mesh->name + "' opened=false ").c_str());
    TwAddButton(bar, (mesh->name + "Unload").c_str(), TwUnloadModel, mesh, (" label='Remove model' Group='" + mesh->name + "' ").c_str());
    //TwAddSeparator(bar, NULL, (" Group='"+ mesh->name +"' ").c_str());
    TwDefine((" TweakBar/" + mesh->name + " Group='Models' Opened=false ").c_str()); //to group all the objects together
    return 1;
}

void TW_CALL TwResetCameraRotation(void *clientData) {
    cam.rotation.x = 0;
    cam.rotation.y = 0;
    cam.rotation.z = 0;
}

void TW_CALL TwLoadModel(void *clientData) {
    
    if (strcasecmp(loadModelName,"bunny")==0)
        insertModel(&meshList, "Bunny", bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);
    else if (strcasecmp(loadModelName,"cube")==0)
        insertModel(&meshList, "Cube", cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
    else if (strcasecmp(loadModelName,"frog")==0)
        insertModel(&meshList, "Frog", frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
    else if (strcasecmp(loadModelName,"cow")==0)
        insertModel(&meshList, "Cow", cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
    else if (strcasecmp(loadModelName,"knot")==0)
        insertModel(&meshList, "Knot", knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
    else if (strcasecmp(loadModelName,"sphere")==0)
        insertModel(&meshList, "Sphere", sphere.nov, sphere.verts, sphere.nof, sphere.faces, 12.0);
    else if (strcasecmp(loadModelName,"teapot")==0)
        insertModel(&meshList, "Teapot", teapot.nov, teapot.verts, teapot.nof, teapot.faces, 0.1);
    else if (strcasecmp(loadModelName,"triceratops")==0)
        insertModel(&meshList, "Triceratops", triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
    else {
        if(!loadModelFromFile(&meshList, "test", loadModelName))
        {
            fprintf(stdout, "Unknown model: %s\n\n", loadModelName);
            strcpy(loadModelName, "Unknown");
            return;
        }
    }
    
    Mesh* mesh = meshList; //Vår mesh är den senaste och ligger därför först

    if(addModelToTwbar(mesh)) {
        calculateBoundingSphere(mesh);
        prepareMesh(mesh);
        fprintf(stdout, "Loaded model: %s\n\n", mesh->name.c_str());
    }
    else {
        removeMeshFromMeshlist(mesh);
        fprintf(stdout, "Failed to load model: %s\n\n", mesh->name.c_str());
    }
}

void TW_CALL SetShader(const void *value, void *clientData)
{
    shader = *(const Shader *)value;  // for instance
    
    if(shader == Phong)
        init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/Phong.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/phong.frag");
    else if(shader == modPhong)
        init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/Phong.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/modphong.frag");
    else if(shader == Cartoon)
        init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/Phong.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/carToon.frag");
    else if(shader == Normal2Color)
        init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/n2c.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/ci.frag");
    else if(shader == Gourad)
        init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/GouradModPhong.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/ci.frag");
}

void TW_CALL GetShader(void *value, void *clientData)
{
    *(Shader *)value = shader;  // for instance
}

void prepareTweakBar() {
    // Set GLUT event callbacks
    // - Directly redirect GLUT mouse button events to AntTweakBar
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    // - Directly redirect GLUT mouse motion events to AntTweakBar
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    // - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    // - Directly redirect GLUT key events to AntTweakBar
    //glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
    ///vi skickar vidare keyboard till tweakbar från vår egen callback function
    // - Directly redirect GLUT special key events to AntTweakBar
    glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
    // - Send 'glutGetModifers' function pointer to AntTweakBar;
    //   required because the GLUT key event functions do not report key modifiers states.
    TwGLUTModifiersFunc(glutGetModifiers);
    
    TwInit(TW_OPENGL_CORE, NULL);
    
    // Create a new TwType to edit Vectors
    TwStructMember VectorMembers[] =
    {
        { "X", TW_TYPE_FLOAT, offsetof(Vector, x), " Step=0.1 " },
        { "Y", TW_TYPE_FLOAT, offsetof(Vector, y), " Step=0.1 " },
        { "Z", TW_TYPE_FLOAT, offsetof(Vector, z), " Step=0.1 " }
    };
    TW_TYPE_VEC = TwDefineStruct("Vector", VectorMembers, 3, sizeof(Vector), NULL, NULL);

    TwEnumVal projectionEV[] = { {Perspective, "Perspective"}, {Frustum, "Frustum"}, {Ortographic, "Ortographic"} };
    TwType TW_TYPE_PROJECTION = TwDefineEnum("TW_TYPE_PROJECTION", projectionEV, 3);
    
    TwEnumVal BoundingVolumeEV[] = { {Sphere, "Sphere"}, {AABB, "AABB"} };
    TwType TW_TYPE_BOUNDINGVOLUME = TwDefineEnum("TW_TYPE_BOUNDINGVOLUME", BoundingVolumeEV, 2);
    
    TwEnumVal shaderEV[] = { {Phong, "Phong"}, {modPhong, "modPhong"}, {Gourad, "Gourad"}, {Cartoon, "Cartoon"}, {Normal2Color, "Normal2Color"} };
    TwType TW_TYPE_SHADER = TwDefineEnum("TW_TYPE_SHADER", shaderEV, 5);
    
    bar = TwNewBar("TweakBar");
    TwDefine(" TweakBar label='Settings' ");
    TwDefine(" TweakBar size='250 500' color='96 216 224' ");
    TwDefine(" TweakBar alpha=180 "); // Opacity of the tweakbar
    TwDefine(" TweakBar refresh=0.1 "); // refresh the bar every 0.1 seconds
    TwDefine(" TW_HELP visible=false ");  // help bar is hidden
    TwDefine(" TweakBar iconifiable=false ");
    TwDefine(" TweakBar visible=false ");
    
    //Camera stuff
    TwAddVarRW(bar, "CamPosition", TW_TYPE_VEC, &cam.position, " label='Camera Position' Group='Camera' help='Change the camera position.' ");
    TwAddVarRW(bar, "CamRotation", TW_TYPE_VEC, &cam.rotation, " label='Camera rotation' Group='Camera' opened=false help='Change the camera rotation.' ");
    TwAddButton(bar, "ResetRotation", TwResetCameraRotation, NULL, " label='Reset Rotation' key=r Group='Camera' help='Reset camera rotation to 0 0 0.'");
    TwAddVarRW(bar, "CamFOV", TW_TYPE_DOUBLE, &cam.fov, " label='Fov' Group='Camera' Max=180 Min=-180 help='Change the camera Feeld of view.' ");
    TwAddVarRW(bar, "CamNear", TW_TYPE_DOUBLE, &cam.nearPlane, " label='Near Plane' Group='Camera' Step=0.1 Min=0.1 ");
    TwAddVarRW(bar, "CamFar", TW_TYPE_DOUBLE, &cam.farPlane, " label='Far Plane' Group='Camera' Step=1 ");
    TwAddVarRW(bar, "Projection", TW_TYPE_PROJECTION, &projection, " label='Projection' Group='Camera' key=p help='Toggle Paralell mode.' ");
    TwAddSeparator(bar, NULL, " Group='Camera' ");
    
    //Shader stuff
    TwAddVarRW(bar, "Lightdir1", TW_TYPE_DIR3F, &lightDir, " label='Light1 Direction' axisx=-x axisy=-y axisz=-z ");
    TwAddVarRW(bar, "Lightdir2", TW_TYPE_DIR3F, &lightDir2, " label='Light2 Direction' axisx=-x axisy=-y axisz=-z ");
    TwAddVarCB(bar, "Shader", TW_TYPE_SHADER, SetShader, GetShader, NULL, " label='Shader' key=m ");
    TwAddVarRW(bar, "", TW_TYPE_FLOAT, &shininess, " label='shininess' ");
    //TwAddVarCB(bar, "Shader", TW_TYPE_Shader, &shader, " label='Shader' key=y' ");
    
    //Culling stuff
    TwAddVarRO(bar, "FPScount", TW_TYPE_FLOAT, &msPerFrame, " label='ms/Frame' Group='Culling' ");
    TwAddVarRW(bar, "BoundingSphereType", TW_TYPE_BOUNDINGVOLUME, &boundingVolume, " label='Bounding Volume' Group='Culling' ");
    TwAddVarRW(bar, "DrawBoundingSphere", TW_TYPE_BOOLCPP, &drawBoundingSphere, " label='Bounding Volume' true=Visible false=Hidden Group='Culling' key=b ");
    
    TwDefine(" TweakBar/Culling opened=false "); //make the model group closed
    
    //Load Model stuff
    TwAddButton(bar, NULL, NULL, NULL, " label='Load a model' group=Models ");
    TwAddVarRW(bar, "modelNameInput", TW_TYPE_CSSTRING(sizeof(loadModelName)), loadModelName, " label='Model Name' group=Models ");
    TwAddButton(bar, NULL, TwLoadModel, NULL, " label='Load' group=Models  ");
    TwDefine(" TweakBar/Models opened=false "); //make the model group closed
    
    //Add Model controls for the preloaded models
    Mesh* mesh = meshList;
    while (mesh != NULL)
    {
        addModelToTwbar(mesh);
        mesh = mesh->next;
    }
    
    
}

int main(int argc, char **argv) {
    
    // Setup freeGLUT ///Probably GLUT and not free glut, since mac...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB | GLUT_3_2_CORE_PROFILE); /// GLUT_DEPTH is Needed to get Z-buffer/depth for assignment 1.3
    glutInitWindowSize(screen_width, screen_height);
    glutCreateWindow("DVA338 Programming Assignments");
    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keypress);
    glutIdleFunc(timerfunc);
    
    const GLint VBL = 0;
    CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &VBL);
    
    // Output OpenGL version info
    fprintf(stdout, "OpenGL version: %s\n", (const char *)glGetString(GL_VERSION));
    fprintf(stdout, "OpenGL vendor: %s\n\n", glGetString(GL_VENDOR));
    
    
    insertModel(&boundingSphere, "boundingSphere", sphere.nov, sphere.verts, sphere.nof, sphere.faces, 1.0);
    
    // Insert the 3D models you want in your scene here in a linked list of meshes
    // Note that "meshList" is a pointer to the first mesh and new meshes are added to the front of the list
    //insertModel(&meshList, "Cow", cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
    insertModel(&meshList, "Triceratops", triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
    calculateBoundingSphere(meshList);
    //loadModelFromFile(&meshList, "Test", "/Users/enari/Desktop/test.obj");
    //calculateBoundingSphere(meshList);
    //insertModel(&meshList, bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);
    //insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
    //insertModel(&meshList, frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
    //insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
    //insertModel(&meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, 12.0);
    //insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 0.1);
    
    prepareTweakBar();
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    
    init("/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/Phong.vert", "/Users/enari/Documents/Repos/DVA338/DVA338/DVA338/shaders/Phong.frag");
    glutMainLoop();
    
    cleanUp();	
    return 0;
}
