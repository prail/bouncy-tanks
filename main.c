#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "game_map.h"
#include "game_object.h"

int main(int argc, char **argv){
    struct game_object *game = NULL;
    game = create_game_object();
    if (!game) {
        return -1;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_map(game->tiles);
    al_flip_display();
    al_start_timer(game->timer);
    while (game->running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(game->event_queue,&ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            game->redraw=true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (game->redraw && al_is_event_queue_empty(game->event_queue)) {
            game->redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            draw_map(game->tiles);
            al_flip_display();
        }
    }
    al_destroy_timer(game->timer);
    al_destroy_display(game->display);
    al_destroy_event_queue(game->event_queue);
    for (int i=0;i<3;i++) {
        al_destroy_bitmap(game->tiles[i]);
    }
    return 0;
    
}