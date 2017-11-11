#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

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
    GAME_OBJECT *game = NULL;
    bool key[4]={false,false,false,false};
    CAMERA_OBJECT *cam = NULL;
    cam=create_camera_object(0,0);
    if (!cam) {
        fprintf(stderr,"failed to create camera object!\n");
        destroy_game_object(game);
        return -1;
    }
    TANK_OBJECT *tank = NULL;
    tank = create_tank_object(0,16*254-4);
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
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(game->timer);
    while (game->running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(game->event_queue,&ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
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
            cam->x += ((tank->x*-1) - cam->x)/30;
            cam->y += ((tank->y*-1) - cam->y)/30;
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
            draw_map(game->tiles,game_map,(SCREEN_W/2)+cam->x,(SCREEN_H/2)+cam->y);
            al_draw_bitmap(game->tiles[3],(SCREEN_W/2)+(cam->x-(tank->x*-1)),(SCREEN_H/2)+(cam->y-(tank->y*-1)),tank_dir);
            al_flip_display();
        }
    }
    destroy_game_object(game);
    destroy_camera_object(cam);
    destroy_tank_object(tank);
    destroy_map_object(game_map);
    return 0;
}