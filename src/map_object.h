#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_


typedef struct map_object {
    int data[256][256];
} MAP_OBJECT;


MAP_OBJECT *create_map_object();
void destroy_map_object(MAP_OBJECT *map);
int map_get_tile(MAP_OBJECT *map, int x, int y);
void draw_map(ALLEGRO_BITMAP **tiles, MAP_OBJECT *map, float offset_x, float offset_y);

#endif