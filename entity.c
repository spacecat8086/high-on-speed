#include "entity.h"

MATRIX3 globalTransform = IDENTITY;
ENTITY trees[TREE_COUNT] = {
    {{155.0f, 135.0f}, {1.0f, 1.0f}, 42.0f},
    {{240.0f, 140.0f}, {1.2f, 1.2f}, 315.0f},
    {{195.0f, 190.0f}, {1.05f, 1.05f}, 28.0f},
    {{120.0f, -15.0f}, {1.0f, 1.0f}, 42.0f},
    {{270.0f, -5.0f}, {1.2f, 1.2f}, 315.0f},
    {{140.0f, 310.0f}, {1.05f, 1.05f}, 28.0f},
    {{40.0f, 210.0f}, {1.05f, 1.05f}, 96.0f},
    {{-20.0f, 115.0f}, {1.0f, 1.0f}, 42.0f},
    {{-27.0f, -15.0f}, {1.2f, 1.2f}, 315.0f},
    {{360.0f, 280.0f}, {1.05f, 1.05f}, 28.0f},
    
    {{-15.0f, -345.0f}, {1.0f, 1.0f}, 42.0f},
    {{80.0f, -215.0f}, {1.2f, 1.2f}, 315.0f},
    {{195.0f, -370.0f}, {1.05f, 1.05f}, 28.0f},
    {{290.0f, -365.0f}, {1.0f, 1.0f}, 42.0f},
    {{270.0f, -205.0f}, {1.2f, 1.2f}, 315.0f},
    {{350.0f, -370.0f}, {1.05f, 1.05f}, 28.0f},
    {{380.0f, -205.0f}, {1.05f, 1.05f}, 96.0f},
    {{460.0f, -360.0f}, {0.95f, 0.95f}, 2.0f},
    {{570.0f, -205.0f}, {1.2f, 1.2f}, 315.0f},
    {{610.0f, -350.0f}, {1.05f, 1.05f}, 28.0f},
    
    {{-115.0f, 135.0f}, {1.0f, 1.0f}, 42.0f},
    {{-240.0f, 115.0f}, {1.2f, 1.2f}, 315.0f},
    {{-195.0f, -30.0f}, {1.05f, 1.05f}, 28.0f},
    {{-290.0f, -30.0f}, {1.0f, 1.0f}, 42.0f},
    {{-370.0f, 15.0f}, {1.2f, 1.2f}, 315.0f},
    {{-450.0f, 130.0f}, {1.05f, 1.05f}, 28.0f},
    {{-380.0f, -205.0f}, {1.05f, 1.05f}, 96.0f},
    {{-320.0f, -240.0f}, {1.0f, 1.0f}, 42.0f},
    {{-270.0f, -395.0f}, {1.2f, 1.2f}, 315.0f},
    {{-110.0f, 340.0f}, {1.05f, 1.05f}, 28.0f},
    
    {{740.0f, -210.0f}, {1.0f, 1.0f}, 42.0f},
    {{780.0f, -170.0f}, {1.2f, 1.2f}, 315.0f},
    {{735.0f, -40.0f}, {1.05f, 1.05f}, 28.0f},
    {{640.0f, -175.0f}, {1.0f, 1.0f}, 42.0f},
    {{670.0f, -210.0f}, {0.9f, 0.9}, 5.0f},
    {{900.0f, -260.0f}, {1.05f, 1.05f}, 28.0f},
    {{920.0f, -175.0f}, {1.05f, 1.05f}, 96.0f},
    {{820.0f, -55.0f}, {1.0f, 1.0f}, 42.0f},
    {{860.0f, -320.0f}, {1.2f, 1.2f}, 315.0f},
    {{795.0f, -330.0f}, {1.05f, 1.05f}, 28.0f},
    
    {{-500.0f, 70.0f}, {1.0f, 1.0f}, 42.0f},
    {{-520.0f, -15.0f}, {1.2f, 1.2f}, 315.0f},
    {{-525.0f, -70.0f}, {1.05f, 1.05f}, 28.0f},
    {{-530.0f, -185.0f}, {1.0f, 1.0f}, 42.0f},
    {{-500.0f, -270.0f}, {1.2f, 1.2f}, 315.0f},
    {{500.0f, -190.0f}, {1.0f, 1.0f}, 42.0f},
    {{420.0f, -150.0f}, {1.1f, 1.1f}, 35.0f},
    {{485.0f, -30.0f}, {1.05f, 1.05f}, 28.0f},
    {{300.0f, -5.0f}, {1.0f, 1.0f}, 42.0f},
    {{420.0f, 100.0f}, {1.2f, 1.2f}, 315.0f}
};

void TransformMesh(PENTITY entity)
{
    MATRIX3 m = IDENTITY;

    Scale(&m, entity->scale.x, entity->scale.y);
    Rotate(&m, entity->angle);
    Translate(&m, entity->pos.x, entity->pos.y);

    // For graphical mesh global transformation is also applied
    Combine(&globalTransform, &m);

    for (int i = 0; i < entity->vCount; i++)
    {
        CopyVector2(&entity->vertices[i], entity->srcMesh[i]);
        Apply(&m, &entity->vertices[i]);
    }    
}

void TransformColMask(PENTITY entity)
{
    MATRIX3 m = IDENTITY;

    Scale(&m, entity->scale.x, entity->scale.y);
    Rotate(&m, entity->angle);
    Translate(&m, entity->pos.x, entity->pos.y);

    // For collision mask only entity tranformations are applied
    for (int i = 0; i < entity->colCount; i++)
    {
        CopyVector2(&entity->collisionMask[i], entity->srcCol[i]);
        Apply(&m, &entity->collisionMask[i]);
    }   
}

void Draw(PENTITY entity, HDC dc)
{
    MATRIX3 m;
    CopyMatrix3(&m, &globalTransform);

    Scale(&m, entity->scale.x, entity->scale.y);
    Rotate(&m, entity->angle);
    Translate(&m, entity->pos.x, entity->pos.y);

    for (int i = 0; i < entity->vCount; i++)
    {
        CopyVector2(&entity->vertices[i], entity->srcMesh[i]);
        Apply(&m, &entity->vertices[i]);
    }
}

void NewMesh(PENTITY entity)
{
    entity->vertices = malloc(sizeof(VECTOR2) * entity->vCount);
}

void NewColMask(PENTITY entity)
{
    entity->collisionMask = malloc(sizeof(VECTOR2) * entity->colCount);
}

void DeleteMesh(PENTITY entity);

int Collision(PENTITY a, PENTITY b)
{
    int result = 0;
    for (int i = 0; i < a->colCount && !result; i++)
    {
        for (int j = 0; j < b->colCount && !result; j++)
        {
            result = Intersects(a->collisionMask[i], a->collisionMask[(i + 1) % a->colCount],
                b->collisionMask[j], b->collisionMask[(j + 1) % b->colCount]);
        }
    }
    return result;
}