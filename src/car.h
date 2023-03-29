#ifndef _CAR_H_
#define _CAR_H_

#include <windows.h>
#include "entity.h"

#define STEERING_RADIUS 70.0f
#define MAX_STEER DEG(1 / STEERING_RADIUS)
#define MAX_STEER_SPEED 150.0f
#define MAX_FRICTION (MAX_STEER_SPEED * MAX_STEER_SPEED / STEERING_RADIUS)
#define STEERING_FRICTION 0.25f
#define ROAD_FRICTION 1.0f
#define AIR_FRICTION 1.0f / 60000000.0f

typedef struct _controls
{
    char up;
    char down;
    char left;
    char right;
} CONTROLS, *PCONTROLS;

typedef struct _car
{
    ENTITY visual;
    CONTROLS controls;
    float v;
} CAR, *PCAR;

void Update(PCAR car, float dt);

#endif