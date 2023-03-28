#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "vector.h"
#include "matrix.h"
#include "mesh.h"

#define TREE_COUNT 50

typedef struct _entity
{
    VECTOR2 pos;
    VECTOR2 scale;
    float angle;
    PVECTOR2 vertices;
    PVECTOR2 srcMesh;
    int vCount;
    PVECTOR2 collisionMask;
    PVECTOR2 srcCol;
    int colCount;
} ENTITY, *PENTITY;

void TransformMesh(PENTITY entity);
void TransformColMask(PENTITY entity);
void NewMesh(PENTITY entity);
void NewColMask(PENTITY entity);
void DeleteMesh(PENTITY entity);
int Collision(PENTITY a, PENTITY b);

#endif