#include <allegro5/allegro.h>

typedef struct map_object {
    int data[256][256];
} MAP_OBJECT;

MAP_OBJECT *create_map_object() {
    MAP_OBJECT *tmp_map = NULL;
    tmp_map = malloc(sizeof(MAP_OBJECT));
    memset(tmp_map, 0, sizeof(MAP_OBJECT));
    tmp_map->data[0][0]=1;
    return tmp_map;
}

void destroy_map_object(MAP_OBJECT *map) {
    if (map) {
        free(map);
    }
}
int map_get_tile(MAP_OBJECT *map, int x, int y) {
    return map->data[y][x];
}    

void draw_map(ALLEGRO_BITMAP **tiles, MAP_OBJECT *map, int offset_x, int offset_y) {
    int n = 0;
    for (int y=0;y<256;y++) {
        for (int x=0;x<256;x++) {
            n=map->data[y][x];
            if (n != 0) {
                al_draw_bitmap(tiles[n-1],(x*16)+offset_x,(y*16)+offset_y,0);
            }
        }
    }
}