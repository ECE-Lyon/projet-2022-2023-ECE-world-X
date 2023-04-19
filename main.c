#include <stdio.h>
#include <stdlib.h>
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
    while (difficulty <= 0 || difficulty > 10) {
        printf("Choose your difficulty (warning it is exponential)\n");
        scanf("%d", &difficulty);
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_init_primitives_addon();
    ALLEGRO_SAMPLE *sample = NULL;

    XYT tabXYT[MAXHITOBJECT];
    XYT printedXYT[MAXHITOBJECT];
    int numHitObjects;
    numHitObjects = getXYTime(difficulty, tabXYT);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();


    int current_point = 0;
    ALLEGRO_EVENT event;
    bool running = true;
    play_music(difficulty, sample);
    int off_beat = clock();
    while (running) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                while (current_point < numHitObjects && clock()-off_beat >= tabXYT[current_point].timing) {
                    printedXYT[current_point] = tabXYT[current_point];
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    draw_circles(printedXYT, off_beat);
                    al_flip_display();
                    current_point++;
                    printf("%ld\n", clock()-off_beat);
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

