#include "matrix.h"

void CopyMatrix3(PMATRIX3 dest, PMATRIX3 src)
{
    for (int i = 0; i < 3 * 3; i++)
    {
        dest->values[i] = src->values[i];
    }
}

void Combine(PMATRIX3 t, PMATRIX3 m)
{
    MATRIX3 result = {{ }};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                result.values[i*3 + j] += t->values[i*3 + k] * m->values[k*3 + j];
            }
        }
    }
    CopyMatrix3(m, &result);
}

void Translate(PMATRIX3 m, float dx, float dy)
{
    MATRIX3 t = TRANSLATION(dx, dy);
    Combine(&t, m);
}

void Scale(PMATRIX3 m, float dx, float dy)
{
    MATRIX3 t = SCALING(dx, dy);
    Combine(&t, m);
}

void Rotate(PMATRIX3 m, float alpha)
{
    MATRIX3 t = ROTATION(RAD(alpha));
    Combine(&t, m);
}

void Apply(PMATRIX3 m, PVECTOR2 v)
{
    VECTOR2 result = { };

    result.x = m->values[0*3 + 0] * v->x + m->values[0*3 + 1] * v->y + m->values[0*3 + 2];
    result.y = m->values[1*3 + 0] * v->x + m->values[1*3 + 1] * v->y + m->values[1*3 + 2];

    CopyVector2(v, result);   
}

void LoadIdentity(PMATRIX3 m)
{
    MATRIX3 id = IDENTITY;
    CopyMatrix3(m, &id);
}