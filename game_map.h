#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#define MAP_W 16
#define MAP_H 10

const int MAP[MAP_H][MAP_W] = {{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                               {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                               {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                               {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                               {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
                               {0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1},
                               {2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,1},
                               {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                               {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                               {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

void draw_map(ALLEGRO_BITMAP **tiles, int offset_x, int offset_y) {
    int n = 0;
    for (int y=0;y<MAP_H;y++) {
        for (int x=0;x<MAP_W;x++) {
            n=MAP[y][x];
            if (n != 0) {
                al_draw_bitmap(tiles[n-1],(x*16)+offset_x,(y*16)+offset_y,0);
            }
        }
    }
}

#endif