#ifndef _TANK_OBJECT_H_
#define _TANK_OBJECT_H_

typedef struct tank_object {
    float x,y;
} TANK_OBJECT;

TANK_OBJECT *create_tank_object(int init_x, int init_y);
void destroy_tank_object(TANK_OBJECT *tank);

#endif