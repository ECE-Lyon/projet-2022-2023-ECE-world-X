//
// Created by benja on 18/04/2023.
//

#include "allegroInits.h"
#include <stdlib.h>
#include <stdio.h>

void initAll() {
    if (!al_init()) {
        printf((const char *) stderr, "Error with (!al_init)\n");
    }

    ALLEGRO_DISPLAY *display = al_create_display(1200, 600);
    if (!display) {
        printf((const char *) stderr, "Error with al_create_display");
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue) {
        printf((const char *) stderr, "Error with event queue init");
        al_destroy_display(display);
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); //fps
    if (!timer) {
        printf((const char *) stderr, "Error with timer init");
        al_destroy_display(display);
        al_destroy_event_queue(queue);
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_init_primitives_addon();
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
}