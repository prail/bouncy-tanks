#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game_map.h"
#include "game_object.h"

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
    struct game_object *game = NULL;
    bool key[4]={false,false,false,false};
    int cam_x=0,cam_y=0;
    game = create_game_object();
    if (!game) {
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_map(game->tiles,cam_x,cam_y);
    al_flip_display();
    al_start_timer(game->timer);
    while (game->running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(game->event_queue,&ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (key[KEY_UP]) {
                cam_y+=5;
            }
            if (key[KEY_DOWN]) {
                cam_y-=5;
            }
            if (key[KEY_LEFT]) {
                cam_x+=5;
            }
            if (key[KEY_RIGHT]) {
                cam_x-=5;
            }
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
            draw_map(game->tiles,cam_x,cam_y);
            al_flip_display();
        }
    }
    destroy_game_object(game);
    return 0;
    
}