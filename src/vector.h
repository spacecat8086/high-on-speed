#ifndef _VECTOR_H_
#define _VECTOR_H_

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>

#define SIGN(a) (a >= 0 ? 1 : -1)

typedef struct _vector2
{
    float x;
    float y;
} VECTOR2, *PVECTOR2;

typedef struct _polygon
{
    int count;
    int *vertices;
    char color[3];
} POLYGON, *PPOLYGON;

void ToPoint(PPOINT p, PVECTOR2 v, int count);
void CopyVector2(PVECTOR2 dest, VECTOR2 src);
float Dot(VECTOR2 a, VECTOR2 b);
float Length(VECTOR2 v);
VECTOR2 Normalize(VECTOR2 v);
VECTOR2 Sum(VECTOR2 a, VECTOR2 b);
VECTOR2 Diff(VECTOR2 a, VECTOR2 b);
VECTOR2 Mul(VECTOR2 a, float k);
VECTOR2 Ortho(VECTOR2 v);
int Intersects(VECTOR2 a0, VECTOR2 a1, VECTOR2 b0, VECTOR2 b1);

#endif