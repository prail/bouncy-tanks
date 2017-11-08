#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define FPS 60.0
#define SCREEN_W 640
#define SCREEN_H 480

const char *tile_names[] = {"img/blue.png","img/bluetop.png","img/door.png"};
const int num_tiles = sizeof(tile_names)/sizeof(*tile_names);

struct game_object {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *tiles[3];
    bool redraw, running;
};

struct game_object *create_game_object() {
    struct game_object *game = malloc(sizeof(struct game_object));
    game->redraw=true;
    game->running=true;
    if (!game) {
        fprintf(stderr, "failed to allocate memory for game object!\n");
        return NULL;
    }
    memset(game->tiles,0,sizeof(game->tiles)/sizeof(*(game->tiles)));
    game->display = NULL;
    game->event_queue = NULL;
    game->timer = NULL;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        free(game);
        return NULL;
    }
    
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize allegro image addon!\n");
        free(game);
        return NULL;
    }
    if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return NULL;
   }
    
    game->timer=al_create_timer(1.0/FPS);
    if (!game->timer) {
        fprintf(stderr, "failed to create timer!\n");
        free(game);
        return NULL;
    }
    game->display = al_create_display(SCREEN_W, SCREEN_H);
    if(!game->display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(game->timer);
        free(game);
        return NULL;
    }
    
    for (int i=0;i<num_tiles;i++) {
        game->tiles[i] = al_load_bitmap(tile_names[i]);
        if (!game->tiles[i]) {
            fprintf(stderr,"failed to load bitmap!\n");
            al_destroy_timer(game->timer);
            al_destroy_display(game->display);
            free(game);
            return NULL;
        }
    }
    
    game->event_queue = al_create_event_queue();
    if (!game->event_queue) {
        fprintf(stderr, "failed to create event queue!\n");
        al_destroy_display(game->display);
        al_destroy_timer(game->timer);
        free(game);
        return NULL;
    }
    
    al_register_event_source(game->event_queue,al_get_display_event_source(game->display));
    al_register_event_source(game->event_queue,al_get_timer_event_source(game->timer));
    al_register_event_source(game->event_queue, al_get_keyboard_event_source());
    return game;
}

void destroy_game_object(struct game_object *game) {
    al_destroy_timer(game->timer);
    al_destroy_display(game->display);
    al_destroy_event_queue(game->event_queue);
    for (int i=0;i<num_tiles;i++) {
        al_destroy_bitmap(game->tiles[i]);
    }
}