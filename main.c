#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "beatmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>



int main() {
    if (!al_init()) {
        printf(stderr, "Error with (!al_init)\n");
        return 1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(1200, 600);
    if (!display) {
        printf(stderr, "Error with al_create_display");
        return 1;
    }

    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (!queue) {
        printf(stderr, "Error with event queue init");
        al_destroy_display(display);
        return 1;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); //fps
    if (!timer) {
        printf(stderr, "Error with timer init");
        al_destroy_display(display);
        al_destroy_event_queue(queue);
        return 1;
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_init_primitives_addon();
    int difficulty = 0;
    while (difficulty <= 0 && difficulty <= 10) {
        printf("Choose your difficulty (warning it is exponential)\n");
        scanf("%d", &difficulty);
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    XYT tabXYT[MAXHITOBJECT];
    int numHitObjects = 0;
    numHitObjects = getXYTime(difficulty, tabXYT);


    int current_point = 0;
    ALLEGRO_EVENT event;
    bool running = true;
    al_start_timer(timer);
    printf("%d", numHitObjects);
    while (running) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                printf("%d\n", al_get_timer_count(timer));
                while (current_point < numHitObjects && tabXYT[current_point].timing/(50/3) <= al_get_timer_count(timer)) {
                    printf("%d", al_get_timer_count(timer));
                    al_draw_filled_circle(tabXYT[current_point].x, tabXYT[current_point].y, 10, al_map_rgb(255, 0, 0));
                    al_flip_display();
                    current_point++;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
// create circles

