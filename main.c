#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include "music.h"
#include "time.h"
#include "ingame.h"
#include <allegro5/allegro_image.h>
#include "menu.h"
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "countdown.h"

int main() {

    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_mouse();
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_DISPLAY *display = al_create_display(1200, 600);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0); //fps
    ALLEGRO_FONT *font = al_load_ttf_font("../design/space_font.ttf", 24, 0);
    ALLEGRO_BITMAP *circle = al_load_bitmap("../design/circle.png");
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    ALLEGRO_EVENT event;
    al_install_keyboard();
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_mouse_state(&mouseState);
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());


    int selected_item = 0;
    int difficulty = 0;
    while (difficulty <= 0) {
        difficulty = inTheMenu(font, queue, selected_item, display);
    }
    int circle_radius = al_get_bitmap_width(circle) / 2;


    XYT tabXYT[MAXHITOBJECT] = {0};
    XYT printedArr[20] = {0};
    int numHitObjects;
    numHitObjects = getXYTime(difficulty, tabXYT);
    countdown(font);

    bool running = true;
    al_start_timer(timer);
    play_music(difficulty, sample);
    int current_point = 0;
    const int off_beat = clock();
    int score = 0;
    int wombocombo = 0;
    int life = 3;

    while (running) {
        // add new points to printedArr
        while (tabXYT[current_point].timing <= clock() - off_beat) {
            addToPrintedArr(tabXYT, printedArr, current_point);
            current_point++;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            printf("oui\n");
        }

        printArr(printedArr, circle);

        al_get_next_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.type) {
                case ALLEGRO_EVENT_KEY_DOWN:
                    IsNoteHit(current_point, tabXYT, off_beat, score, wombocombo, life);
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    running = false;
                    break;

            }
        }
    }


    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
// create circles

