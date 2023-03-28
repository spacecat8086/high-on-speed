#include "vector.h"

void ToPoint(PPOINT p, PVECTOR2 v, int count)
{
    for (int i = 0; i < count; i++)
    {
        p[i].x = (int) v[i].x;
        p[i].y = (int) v[i].y;
    }
}

void CopyVector2(PVECTOR2 dest, VECTOR2 src)
{
    dest->x = src.x;
    dest->y = src.y;
}

float Length(VECTOR2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

VECTOR2 Sum(VECTOR2 a, VECTOR2 b)
{
    VECTOR2 s = { a.x + b.x, a.y + b.y };
    return s;
}

VECTOR2 Diff(VECTOR2 a, VECTOR2 b)
{
    VECTOR2 s = { a.x - b.x, a.y - b.y };
    return s;
}

VECTOR2 Normalize(VECTOR2 v)
{
    float len = Length(v);
    VECTOR2 n = { v.x / len, v.y / len };
    return n;
}

VECTOR2 Mul(VECTOR2 a, float k)
{
    VECTOR2 v = { a.x * k, a.y * k};
    return v;
}

VECTOR2 Ortho(VECTOR2 v)
{
    VECTOR2 n = { -v.y, v.x };
    return n;
}
/*
int Intersects(VECTOR2 a0, VECTOR2 a1, VECTOR2 b0, VECTOR2 b1)
{
    VECTOR2 av = Diff(a1, a0);
    VECTOR2 bv = Diff(b1, b0);

    if (a0.x > a)
    
   
}
*/
float Area(VECTOR2 a, VECTOR2 b, VECTOR2 c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
int CheckBoundingBox(float a, float b, float c, float d)
{
	if (a > b)
    {
        float temp = b;
        b = a;
        a = temp;
    }
	if (c > d)
    {
        float temp = d;
        d = c;
        c = temp;
    }
	return max(a, c) <= min(b, d);
}
 
int Intersects(VECTOR2 a0, VECTOR2 a1, VECTOR2 b0, VECTOR2 b1) 
{
	return CheckBoundingBox (a0.x, a1.x, b0.x, b1.x)
		&& CheckBoundingBox (a0.y, a1.y, b0.y, b1.y)
		&& Area(a0, a1, b0) * Area(a0, a1, b1) <= 0
		&& Area(b0, b1, a0) * Area(b0, b1, a1) <= 0;
}