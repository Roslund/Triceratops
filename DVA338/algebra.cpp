#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>
#include <stdio.h>
#include "algebra.h"

float cotan(float deg)
{
    return 1/tan(deg*(M_PI/180));
}

//qw + i qx + j qy + k qz
Matrix rotationQuaternion(HomVector q)
{
    Matrix temp;
    temp.e[0] = 1-(2*q.y*q.y)-(2*q.z*q.z);  temp.e[4] = (2*q.x*q.y)-(2*q.z*q.w);    temp.e[8] = (2*q.x*q.z)+(2*q.y*q.w);    temp.e[12] = 0.0f;
    temp.e[1] = (2*q.x*q.y)+(2*q.z*q.w);    temp.e[5] = 1-(2*q.x*q.x)-(2*q.z*q.z);  temp.e[9] = (2*q.y*q.z)-(2*q.x*q.w);    temp.e[13] = 0.0f;
    temp.e[2] = (2*q.x*q.z)-(2*q.y*q.w);    temp.e[6] = (2*q.y*q.z)+(2*q.x*q.w);    temp.e[10] = 1-(2*q.x*q.x)-(2*q.y*q.y); temp.e[14] = 0.0f;
    temp.e[3] = 0.0f;                       temp.e[7] = 0.0f;                       temp.e[11] = 0.0f;                      temp.e[15] = 1.0f;
    return temp;
}

Matrix generatePerspectiveProjectionMatrix(int width, int height, double n, double f, double fov)
{
    Matrix P;
    float aspectRatio = width / (float)height;
    
    for (int i = 0; i < 16; i++)
    {
        P.e[i] = 0.0f;
    }
    
    P.e[0] = cotan(fov/2.0f) / aspectRatio;
    P.e[5] = cotan(fov/2.0f);
    P.e[10] = (f + n) / (n - f);
    P.e[11] = -1.0f;
    P.e[14] = (2.0f * f * n) / (n - f);
    
    return P;
}

Matrix generateOrthographicProjectionMatrix(int width, int height, double n, double f, double fov)
{
    Matrix P;
    float aspectRatio = width / (float)height;
    
    float scale = tan(fov * 0.5f * M_PI / 180) * n;
    float r = aspectRatio * scale;
    float l = -r;
    float t = scale;
    float b = -t;
    
    P.e[0] = 2.0f/(r-l);    P.e[4] = 0.000000f;     P.e[ 8] = 0.000000f;     P.e[12] = -((r+l)/(r-l));
    P.e[1] = 0.000000f;     P.e[5] = 2.0f/(t-b);    P.e[ 9] = 0.000000f;     P.e[13] = -((t+b)/(t-b));
    P.e[2] = 0.000000f;     P.e[6] = 0.000000f;     P.e[10] = (-2.0f)/(f-n); P.e[14] = -((f+n)/(f-n));
    P.e[3] = 0.000000f;     P.e[7] = 0.000000f;     P.e[11] = 0.000000f;     P.e[15] = 1.0f;
    
    return P;
}

//Frustum
Matrix generateFrustumProjectionMatrix(int width, int height, double n, double f, double fov)
{
    Matrix P;
    float aspectRatio = width / (float)height;
    
    float scale = tan((fov * 0.5f) * (M_PI / 180)) * n;
    float r = aspectRatio * scale;
    float l = -r;
    float t = scale;
    float b = -t;
    
    P.e[0] = (2.0f*n)/(r-l);    P.e[4] = 0.000000f;     P.e[ 8] =  (l+r)/(l-r); P.e[12] =  0.0f;
    P.e[1] = 0.000000f;         P.e[5] = (2*n)/(t-b);   P.e[ 9] =  (b+t)/(b-t); P.e[13] =  0.0f;
    P.e[2] = 0.000000f;         P.e[6] = 0.000000f;     P.e[10] = (f+n)/(n-f);  P.e[14] = (2*f*n)/(n-f);
    P.e[3] = 0.000000f;         P.e[7] = 0.000000f;     P.e[11] = -1.000000f;   P.e[15] =  0.0f;
    
    return P;
}

Matrix translate(float x, float y, float z)
{
    Matrix temp;
    temp.e[0] = 1.0f; temp.e[4] = 0.0f; temp.e[8] = 0.0f; temp.e[12] = x;
    temp.e[1] = 0.0f; temp.e[5] = 1.0f; temp.e[9] = 0.0f; temp.e[13] = y;
    temp.e[2] = 0.0f; temp.e[6] = 0.0f; temp.e[10] = 1.0f; temp.e[14] = z;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix translate(Vector in)
{
    Matrix temp;
    temp.e[0] = 1.0f; temp.e[4] = 0.0f; temp.e[8] = 0.0f; temp.e[12] = in.x;
    temp.e[1] = 0.0f; temp.e[5] = 1.0f; temp.e[9] = 0.0f; temp.e[13] = in.y;
    temp.e[2] = 0.0f; temp.e[6] = 0.0f; temp.e[10] = 1.0f; temp.e[14] = in.z;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix scale(float x, float y, float z)
{
    Matrix temp;
    temp.e[0] = x; temp.e[4] = 0.0f; temp.e[8] = 0.0f; temp.e[12] = 0.0f;
    temp.e[1] = 0.0f; temp.e[5] = y; temp.e[9] = 0.0f; temp.e[13] = 0.0f;
    temp.e[2] = 0.0f; temp.e[6] = 0.0f; temp.e[10] = z; temp.e[14] = 0.0f;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix scale(Vector in)
{
    Matrix temp;
    temp.e[0] = in.x; temp.e[4] = 0.0f; temp.e[8] = 0.0f; temp.e[12] = 0.0f;
    temp.e[1] = 0.0f; temp.e[5] = in.y; temp.e[9] = 0.0f; temp.e[13] = 0.0f;
    temp.e[2] = 0.0f; temp.e[6] = 0.0f; temp.e[10] = in.z; temp.e[14] = 0.0f;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix rotationX(float rad)
{
    Matrix temp;
    temp.e[0] = 1.0f; temp.e[4] = 0.0f; temp.e[8] = 0.0f; temp.e[12] = 0.0f;
    temp.e[1] = 0.0f; temp.e[5] = cosf(rad); temp.e[9] = -sinf(rad); temp.e[13] = 0.0f;
    temp.e[2] = 0.0f; temp.e[6] = sinf(rad); temp.e[10] = cosf(rad); temp.e[14] = 0.0f;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix rotationY(float rad)
{
    Matrix temp;
    temp.e[0] = cosf(rad); temp.e[4] = 0.0f; temp.e[8] = sinf(rad); temp.e[12] = 0.0f;
    temp.e[1] = 0.0f; temp.e[5] = 1.0f; temp.e[9] = 0.0f; temp.e[13] = 0.0f;
    temp.e[2] = -sinf(rad); temp.e[6] = 0.0f; temp.e[10] = cosf(rad); temp.e[14] = 0.0f;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Matrix rotationZ(float rad)
{
    Matrix temp;
    temp.e[0] = cosf(rad); temp.e[4] = -sinf(rad); temp.e[8] = 0.0f; temp.e[12] = 0.0f;
    temp.e[1] = sinf(rad); temp.e[5] = cosf(rad); temp.e[9] = 0.0f; temp.e[13] = 0.0f;
    temp.e[2] = 0.0f; temp.e[6] = 0.0f; temp.e[10] = 1.0f; temp.e[14] = 0.0f;
    temp.e[3] = 0.0f; temp.e[7] = 0.0f; temp.e[11] = 0.0f; temp.e[15] = 1.0f;
    return temp;
}

Vector CrossProduct(Vector a, Vector b) {
    Vector v = { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
    return v;
}

float DotProduct(Vector a, Vector b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector Subtract(Vector a, Vector b) {
    Vector v = { a.x-b.x, a.y-b.y, a.z-b.z };
    return v;
}

Vector Add(Vector a, Vector b) {
    Vector v = { a.x+b.x, a.y+b.y, a.z+b.z };
    return v;
}

float Length(Vector a) {
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vector Normalize(Vector a) {
    float len = Length(a);
    Vector v = { a.x/len, a.y/len, a.z/len };
    return v;
}

Vector ScalarVecMul(float t, Vector a) {
    Vector b = { t*a.x, t*a.y, t*a.z };
    return b;
}

HomVector MatVecMul(Matrix a, Vector b) {
    HomVector h;
    h.x = b.x*a.e[0] + b.y*a.e[4] + b.z*a.e[8] + a.e[12];
    h.y = b.x*a.e[1] + b.y*a.e[5] + b.z*a.e[9] + a.e[13];
    h.z = b.x*a.e[2] + b.y*a.e[6] + b.z*a.e[10] + a.e[14];
    h.w = b.x*a.e[3] + b.y*a.e[7] + b.z*a.e[11] + a.e[15];
    return h;
}

Vector Homogenize(HomVector h) {
    Vector a;
    if (h.w == 0.0) {
        fprintf(stderr, "Homogenize: w = 0\n");
        a.x = a.y = a.z = 9999999;
        return a;
    }
    a.x = h.x / h.w;
    a.y = h.y / h.w;
    a.z = h.z / h.w;
    return a;
}

Matrix MatMatMul(Matrix a, Matrix b) {
    Matrix c;
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            c.e[j*4+i] = 0.0;
            for (k = 0; k < 4; k++)
                c.e[j*4+i] += a.e[k*4+i] * b.e[j*4+k];
        }
    }
    return c;
}

void PrintVector(char *name, Vector a) {
    printf("%s: %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z);
}

void PrintHomVector(char *name, HomVector a) {
    printf("%s: %6.5lf %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z, a.w);
}

void PrintMatrix(char *name, Matrix a) {
    int i,j;
    
    printf("%s:\n", name);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%6.5lf ", a.e[j*4+i]);
        }
        printf("\n");
    }
}
