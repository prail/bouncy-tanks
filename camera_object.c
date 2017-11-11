#include <stdlib.h>

typedef struct camera_object {
    int x,y;
} CAMERA_OBJECT;

CAMERA_OBJECT *create_camera_object(int init_x,int init_y) {
    CAMERA_OBJECT *tmp_cam = NULL;
    tmp_cam = malloc(sizeof(CAMERA_OBJECT));
    if (tmp_cam) {
        tmp_cam->x = init_x;
        tmp_cam->y = init_y;
        return tmp_cam;
    }
    return NULL;
}

void destroy_camera_object(CAMERA_OBJECT *camera) {
    if (camera) {
        free(camera);
    }
}