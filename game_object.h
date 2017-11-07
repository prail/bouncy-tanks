#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#define FPS 60.0
#define SCREEN_W 640
#define SCREEN_H 480

struct game_object {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *tiles[3];
    bool redraw, running;
};

struct game_object *create_game_object();

#endif