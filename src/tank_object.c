#include <stdlib.h>

typedef struct tank_object {
    float x,y;
} TANK_OBJECT;

TANK_OBJECT *create_tank_object(int init_x, int init_y) {
    TANK_OBJECT *tmp_tank = NULL;
    tmp_tank = malloc(sizeof(TANK_OBJECT));
    if (tmp_tank) {
        tmp_tank->x = (float)init_x;
        tmp_tank->y = (float)init_y;
        return tmp_tank;
    }
    return NULL;
}

void destroy_tank_object(TANK_OBJECT *tank) {
    if (tank) {
        free(tank);
    }
}
