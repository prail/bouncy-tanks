#ifndef _CAMERA_OBJECT_H_
#define _CAMERA_OBJECT_H_

typedef struct camera_object {
    int x,y;
} CAMERA_OBJECT;

CAMERA_OBJECT *create_camera_object(int init_x,int init_y);
void destroy_camera_object(CAMERA_OBJECT *camera);

#endif