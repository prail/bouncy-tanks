#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


#define FPS 60.0
#define SCREEN_W 640
#define SCREEN_H 480


#define MAP_W 16
#define MAP_H 10

const char *tile_names[] = {"blue.png","bluetop.png","door.png"};
const int num_tiles = sizeof(tile_names)/sizeof(*tile_names);
const int MAP[MAP_H][MAP_W] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0},
                               {0,0,0,0,0,2,1,1,1,0,0,0,0,0,0,0},
                               {0,0,0,0,2,1,1,1,1,0,0,0,0,0,0,0},
                               {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
/* Basic idea for collision, involves this:
** Every part of the game is rendered by a whole bunch of lines.
** Check if the player's "line" intersects with any of the onscreen lines.
** If it does then a collision is encountered.
** 
** 
**  
** 
** 
*/
void draw_map(ALLEGRO_BITMAP **tiles) {
    int n = 0;
    for (int y=0;y<MAP_H;y++) {
        for (int x=0;x<MAP_W;x++) {
            n=MAP[y][x];
            if (n != 0) {
                al_draw_bitmap(tiles[n-1],x*16,y*16,0);
            }
        }
    }
}


int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *tiles[num_tiles];
    bool redraw = true, running = true;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize allegro image addon!\n");
        return -1;
    }
    
    timer=al_create_timer(1.0/FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    for (int i=0;i<num_tiles;i++) {
        tiles[i] = al_load_bitmap(tile_names[i]);
    }
    
    /*
    if (!image) {
        fprintf(stderr,"failed to load bitmap!\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    */
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_map(tiles);
    al_flip_display();
    al_start_timer(timer);
    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw=true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            draw_map(tiles);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    for (int i=0;i<num_tiles;i++) {
        al_destroy_bitmap(tiles[i]);
    }
    return 0;
    
}