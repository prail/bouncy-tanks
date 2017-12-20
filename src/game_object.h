#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#define FPS 60.0
#define SCREEN_W 640
#define SCREEN_H 480

typedef struct game_object {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *tiles[16];
    bool redraw, running;
} GAME_OBJECT;

GAME_OBJECT *create_game_object();
void destroy_game_object(GAME_OBJECT *game);
#endif