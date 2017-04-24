#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

typedef struct { float x, y, z; } Vector;
typedef struct { float x, y, z, w; } HomVector;

/* Column-major order are used for the matrices here to be compatible with OpenGL.
 ** The indices used to access elements in the matrices are shown below.
 **  _                _
 ** |                  |
 ** |   0   4   8  12  |
 ** |                  |
 ** |   1   5   9  13  |
 ** |                  |
 ** |   2   6  10  14  |
 ** |                  |
 ** |   3   7  11  15  |
 ** |_                _|
 */
typedef struct matrix { float e[16]; } Matrix;

Matrix rotationQuaternion(HomVector q);
Matrix generatePerspectiveProjectionMatrix(int width, int height, double near, double far, double fov);
Matrix generateOrthographicProjectionMatrix(int width, int height, double n, double f, double fov);
Matrix generateFrustumProjectionMatrix(int width, int height, double near, double far, double fov);
Matrix translate(float x, float y, float z);
Matrix scale(float x, float y, float z);
Matrix scale(Vector in);
Matrix rotationX(float rad);
Matrix rotationY(float rad);
Matrix rotationZ(float rad);
Vector Add(Vector a, Vector b);
Vector Subtract(Vector a, Vector b);
Vector CrossProduct(Vector a, Vector b);
float DotProduct(Vector a, Vector b);
float DotProduct(HomVector a, HomVector b);
float Length(Vector a);
Vector Normalize(Vector a);
HomVector NormalizePlane(HomVector a);
Vector ScalarVecMul(float t, Vector a);
HomVector MatVecMul(Matrix a, Vector b);
Vector Homogenize(HomVector a);
Matrix MatMatMul(Matrix a, Matrix b);
void PrintMatrix(char *name, Matrix m);
void PrintVector(char *name, Vector v);
void PrintHomVector(char *name, HomVector h);

#endif

