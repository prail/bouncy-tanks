#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#include "map_object.h"
#include "game_object.h"
#include "camera_object.h"
#include "tank_object.h"

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

void key_handler(bool key_arr[4], int code, bool set_val) {
    switch(code) {
        case ALLEGRO_KEY_UP:
            key_arr[KEY_UP] = set_val;
            break;
        case ALLEGRO_KEY_DOWN:
            key_arr[KEY_DOWN] = set_val;
            break;
        case ALLEGRO_KEY_LEFT: 
            key_arr[KEY_LEFT] = set_val;
            break;
        case ALLEGRO_KEY_RIGHT:
            key_arr[KEY_RIGHT] = set_val;
            break;
    }
}

int main(int argc, char **argv){
    srand(time(NULL));
    GAME_OBJECT *game = NULL;
    bool key[4]={false,false,false,false};
    CAMERA_OBJECT *cam = NULL;
    cam=create_camera_object(0,0); /*Puts the camera object at the map's origin.*/
    if (!cam) {
        fprintf(stderr,"failed to create camera object!\n");
        destroy_game_object(game);
        return -1;
    }
    TANK_OBJECT *tank = NULL;
    tank = create_tank_object(0,16*254-4);/*Puts the tank at the bottom of the map*/
    if (!tank) {
        fprintf(stderr,"failed to create tank object!\n");
        destroy_game_object(game);
        destroy_camera_object(cam);
        return -1;
    }
    MAP_OBJECT *game_map = NULL;
    game_map = create_map_object();
    if (!game_map) {
        fprintf(stderr,"failed to create map object!\n");
        destroy_game_object(game);
        destroy_camera_object(cam);
        destroy_tank_object(tank);
        return -1;
    }
    int tank_dir=0;
    game = create_game_object();
    if (!game) {
        return -1;
    }
    for (int i=0;i<255;i++) {
        for (int j=0;j<255;j++) {
            if (rand()%100 < 5) game_map->data[j][i]=1;
        }
    }
    int tank_width=al_get_bitmap_width(game->tiles[3]),tank_height=al_get_bitmap_height(game->tiles[3]);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(game->timer);
    int set_x, set_y, old_x, old_y;
    while (game->running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(game->event_queue,&ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            old_x = tank->x;
            old_y = tank->y;
            if (key[KEY_UP]) {
                tank->y-=5;
            }
            if (key[KEY_DOWN]) {
                tank->y+=5;
            }
            if (key[KEY_LEFT]) {
                tank->x-=5;
                tank_dir=0;
            }
            if (key[KEY_RIGHT]) {
                tank->x+=5;
                tank_dir=ALLEGRO_FLIP_HORIZONTAL;
            }
            /*Put tile based collision code here.*/
            /*
            tank->y+=5;
            while (((tank->y+(tank_width/3))/16)+1 > 255) {
                tank->y-=5;
            }
            */
            cam->x += ((tank->x*-1) - cam->x)/5;
            cam->y += ((tank->y*-1) - cam->y)/5;
            //printf("gridx: %d, gridy: %d x: %d, y: %d\n", (tank->x-(tank_width/2))/16,(tank->x-(tank_width/2))/16, tank->x, tank->y);
            set_y=(int)((tank->y)/16);
            set_x=(int)((tank->x)/16);
            /*This entire abuse of macros needs to be cleaned up.*/
            #define CHECKSET(xoff,yoff) \
            do {\
                if (set_x+xoff > -1 && set_x+xoff < 256 && set_y+yoff > -1 && set_y+yoff < 256) {\
                    if (game_map->data[set_y+yoff][set_x+xoff] == 1) {\
                      tank->x=old_x;\
                      tank->y=old_y;\
                    }\
                }\
            } while(0)
            CHECKSET(0,0);
            CHECKSET(1,0);
            CHECKSET(-1,0);
            CHECKSET(0,1);
            CHECKSET(0,-1);
            /*Diagonal checks.*/
            CHECKSET(-1,-1);
            CHECKSET(1,-1);
            CHECKSET(1,1);
            CHECKSET(-1,1);
            
            game->redraw=true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            game->running=false;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key_handler(key,ev.keyboard.keycode,true);
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key_handler(key,ev.keyboard.keycode,false);
        }
        if (game->redraw && al_is_event_queue_empty(game->event_queue)) {
            game->redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            /*This does all of the rendering work. Will move to function soon.*/
            draw_map(game->tiles,game_map,(SCREEN_W/2)+cam->x,(SCREEN_H/2)+cam->y);
            al_draw_bitmap(game->tiles[3],((SCREEN_W/2)+(cam->x-(tank->x*-1)))-(tank_width/2),((SCREEN_H/2)+(cam->y-(tank->y*-1)))-(tank_height/2),tank_dir);
            al_flip_display();
        }
    }
    destroy_game_object(game);
    destroy_camera_object(cam);
    destroy_tank_object(tank);
    destroy_map_object(game_map);
    return 0;
}