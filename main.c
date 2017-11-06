#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

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




int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *tiles[8];
    memset(tiles,0,sizeof(ALLEGRO_BITMAP*)*8);
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
    
    tiles[0] = al_load_bitmap("bluetop.png");
    tiles[1] = al_load_bitmap("blue.png");
    
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
    al_draw_bitmap(tiles[0],0.0,0.0,0);
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
            al_draw_bitmap(tiles[0],0,0,0);
            al_draw_bitmap(tiles[1],16,0,0);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    for (int i=0;i<8;i++) {
        if (tiles[i] != 0) {
            al_destroy_bitmap(tiles[i]);
        }
    }
    return 0;
    
}