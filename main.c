#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include "music.h"
#include "time.h"
#include "ingame.h"


int main() {
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
    }

    if (!al_install_audio()) {
        fprintf(stderr, "Failed to initialize audio!\n");
        return -1;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }

    int difficulty = 0;
    while (difficulty <= 0 && difficulty <= 10) {
        printf("Choose your difficulty (warning it is exponential)\n");
        scanf("%d", &difficulty);
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_init_primitives_addon();
    ALLEGRO_SAMPLE *sample = NULL;

    XYT tabXYT[MAXHITOBJECT] = {0};
    XYT printedArr[20] = {0};
    int numHitObjects;
    numHitObjects = getXYTime(difficulty, tabXYT);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();


    al_clear_to_color(al_map_rgb(0, 0, 0)); // move clear call here
    al_flip_display();
    ALLEGRO_EVENT event;
    bool running = true;
    al_start_timer(timer);
    play_music(difficulty, sample);
    int current_point = 0;
    printf("%ld", clock());

    while (running) {
        // add new points to printedArr
        while (tabXYT[current_point].timing+500 <= clock() - 1900) { //problème avec l'offbeat inconstant
            addToPrintedArr(tabXYT, printedArr, current_point);
            current_point++;
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

        printArr(printedArr);

        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
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

