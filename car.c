#include "car.h"

void Update(PCAR car, float dt)
{
    float a = 0.0f;
    if (car->v > 0.0f)
    {
        if (car->controls.down)
        {
            a = -200.0f;
        }
        else if (car->controls.up)
        {
            a = car->v <= 150.0f ? 150.0f : 22500.0f / car->v;
        }
        else
        {
            a = car->v <= 250.0f ? -40.0f : -10000.0f / car->v;
        }
        
    }
    else
    {
        if (car->controls.up)
        {
            a = 200;
        }
        else if (car->controls.down)
        {
            a = car->v >= -150.0f ? -150.0f : 0.0f;
        }
        else
        {
            a = 40.0f;
        }
        
    }

    float steer = (car->controls.right - car->controls.left) * MAX_STEER;
    float steerFriction = RAD(steer) * car->v * car->v;

    if (fabs(steerFriction) > MAX_FRICTION)
    {   
        steerFriction = SIGN(steerFriction) * MAX_FRICTION;
        steer = DEG(steerFriction / car->v / car->v);
    }

    float dAngle = steer * car->v * dt;
    car->visual.angle += dAngle;

    car->v -= SIGN(car->v) * STEERING_FRICTION * fabs(steerFriction) * dt;
    car->v -= ROAD_FRICTION * dt;
    car->v += a * dt;
    car->v *= (1.0f - AIR_FRICTION * car->v * car->v * dt);
    

    car->visual.pos.x += (car->v * cos(RAD(car->visual.angle))) * dt;
    car->visual.pos.y += (car->v * sin(RAD(car->visual.angle))) * dt;
}