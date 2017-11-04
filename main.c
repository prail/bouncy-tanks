#include <stdio.h>
#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "intersect.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

typedef struct line {
    long x1,y1,x2,y2;
} LINE;

LINE *create_line(int x1, int y1, int x2, int y2) {
    LINE *temp = malloc(sizeof(LINE));
    temp->x1 = x1;
    temp->x2 = x2;
    temp->y1 = y1;
    temp->y2 = y2;
    return temp;
}

int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    //ALLEGRO_BITMAP *image = NULL;
    bool redraw = true, running = true;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    /*
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize allegro image addon!\n");
        return -1;
    }
    */
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
    /*
    image = al_load_bitmap("tank.png");
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
    
    LINE *line_1 = create_line(0,5,10,5);
    LINE *line_2 = create_line(5,0,5,10);
    long intersect_x,intersect_y;
    int intersection = lines_intersect(line_1->x1,line_1->y1,line_1->x2,line_1->y2,line_2->x1,line_2->y1,line_2->x2,line_2->y2,&intersect_x,&intersect_y);
    if (intersection == DO_INTERSECT) {
        printf("Lines intersect at %d, %d",intersect_x,intersect_y);
    }
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0,0,0));
    //al_draw_bitmap(image,0.0,0.0,0);
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
            //al_draw_bitmap(image,0.0,0.0,0);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    //al_destroy_bitmap(image);
    return 0;
    
}