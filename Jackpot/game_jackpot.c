#include "const_jackpot.h"
#include "Roll_and_handle.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "const_jackpot.h"

int game_jackpot(ALLEGRO_DISPLAY* display) {
    int endgame = 0, pause = 0;
    float acceleration = 0.1, max_speed = 10.0;

    Roll roll[NB_ROLLS];
    Handle handle;
    handle.down = false;
    for (int i = 0; i < NB_ROLLS; ++i) {
        roll[i].rotation_speed = 1.0;
    }
    //ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *fontBig = NULL;
    ALLEGRO_EVENT event;

    roll[0].location_x = X_ROLL1;
    roll[1].location_x = X_ROLL2;
    roll[2].location_x = X_ROLL3;

    srand(time(NULL));

    /*if (!al_init()) {
        error_jackpot("Initialisation Allegro");
    }
    if (!al_install_keyboard()) {
        error_jackpot("Keyboard download");
    }
    if (!al_install_mouse()) {
        error_jackpot("Mouse download");
    }
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        error_jackpot("Initialisation fonts");
    }
    if (!al_init_primitives_addon()) {
        error_jackpot("Initialisation primitives");
    }
    if (!al_init_image_addon()) {
        error_jackpot("Initialisation images");
    }

    //display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    al_set_window_position(display, 200, 100);
    if (!display) {
        error_jackpot("Display creation");
    }*/

    timer = al_create_timer(1.0 / 60.0);

    if (!timer) {
        al_destroy_display(display);
        al_destroy_font(font);
        error_jackpot("Timer creation");
    }


    queue = al_create_event_queue();
    if (!queue) {
        al_destroy_display(display);
        al_destroy_font(font);
        al_destroy_timer(timer);
        error_jackpot("Event queue creation");
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    init_images_jackpot(roll, &handle);
    init_rolls(roll);

    al_start_timer(timer);

    font = al_load_ttf_font("../Ships/Pictures/Starjedi.ttf", 18, 0);
    fontBig = al_load_ttf_font("../Ships/Pictures/Starjedi.ttf", 35, 0);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    do {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            endgame = 1;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            switch (event.mouse.button) {
                case 1:
                    if (event.mouse.x >= 856 && event.mouse.x <= 933 && event.mouse.y >= 192 &&
                        event.mouse.y <= 265) {      //hitbox for the handle
                        handle.down = true;
                    }
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN && !pause) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_P:
                    pause = true;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    endgame = 1;
                    break;

                case ALLEGRO_KEY_SPACE:
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP && !pause) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_P:
                    pause = false;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            if (event.timer.source == timer) {
                al_clear_to_color(al_map_rgb(0, 0, 0));

                if (!pause) {

                    display_background(handle);
                    display_rolls(roll);
                    display_Machine(handle, font);
                    al_flip_display();
                    if (handle.down == true) {
                        rolling(roll, acceleration, max_speed);
                    }

                    if (handle.down == true) {
                        rolling(roll, acceleration, max_speed);
                    }
                    if (event.timer.count % 60 == 0) {

                    }
                }
            }
        }

        if (al_is_event_queue_empty(queue)) {
            if (pause) {
                al_stop_timer(timer);
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "pause");
            }
            al_flip_display();
        }

    } while (!endgame);

    al_destroy_bitmap(handle.Machine_up);
    al_destroy_bitmap(handle.Machine_down);
    al_destroy_bitmap(handle.Machine_background);
    al_destroy_bitmap(roll->Picture1);
    al_destroy_bitmap(roll->Picture2);
    al_destroy_bitmap(roll->Picture3);
    al_destroy_bitmap(roll->Picture4);
    al_destroy_bitmap(roll->Picture5);
    al_destroy_bitmap(roll->Picture6);
    al_destroy_bitmap(roll->Picture7);
    al_destroy_bitmap(roll->Picture8);
    al_destroy_bitmap(roll->Picture9);

    al_destroy_font(font);
    al_destroy_font(fontBig);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

//
    return 0;
}