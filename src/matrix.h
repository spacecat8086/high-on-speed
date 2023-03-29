#ifndef _MATRIX_H_
#define _MATRIX_H_

#define _USE_MATH_DEFINES

#include "vector.h"
#include "math.h"

#define RAD(a) (a * M_PI / 180.0)
#define DEG(a) (a * 180.0 / M_PI)

#define IDENTITY {{\
    1.0f, 0.0f, 0.0f,\
    0.0f, 1.0f, 0.0f,\
    0.0f, 0.0f, 1.0f\
}}

#define TRANSLATION(dx, dy) {{\
    1.0f, 0.0f, (dx),\
    0.0f, 1.0f, (dy),\
    0.0f, 0.0f, 1.0f\
}}

#define SCALING(sx, sy) {{\
    (sx), 0.0f, 0.0f,\
    0.0f, (sy), 0.0f,\
    0.0f, 0.0f, 1.0f\
}}

#define ROTATION(a) {{\
    cos(a), -sin(a), 0.0f,\
    sin(a),  cos(a), 0.0f,\
    0.0f,      0.0f, 1.0f\
}}

typedef struct _matrix3
{
    float values[3 * 3];
} MATRIX3, *PMATRIX3;

PMATRIX3 NewMatrix3();
void FreeMatrix3(PMATRIX3 m);
void CopyMatrix3(PMATRIX3 dest, PMATRIX3 src);
void Combine(PMATRIX3 t, PMATRIX3 m);
void Translate(PMATRIX3 m, float dx, float dy);
void Scale(PMATRIX3 m, float dx, float dy);
void Rotate(PMATRIX3 m, float alpha);
void Apply(PMATRIX3 m, PVECTOR2 v);
void LoadIdentity(PMATRIX3 m);

#endif