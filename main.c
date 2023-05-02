#include "Ship.h"
#include "Start_and_images.h"
#include "const.h"
#include "Player_crosshair.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int main() {
    int endgame = 0, gameover = 0, pause = 0, start = 0, ingame = 0, destroyedShips = 0, scoreP1 = 0, scoreP2 = 0;
    FPSdisplay turret;
    Ship ships[NB_SHIPS];
    Crosshair crosshair;
    Player P1;
    P1.name = 22;
    P1.turn = 1;
    Player P2;
    P2.name = 23;
    P2.turn = 0;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *count = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *fontBig = NULL;
    ALLEGRO_EVENT event;

    srand(time(NULL));

    if (!al_init()) {
        error("Initialisation Allegro");
    }
    if (!al_install_keyboard()) {
        error("Keyboard download");
    }
    if (!al_install_mouse()) {
        error("Mouse download");
    }
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        error("Initialisation fonts");
    }
    if (!al_init_image_addon()) {
        error("Initialisation images");
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    al_set_window_position(display, 200, 100);
    if (!display) {
        error("Display creation");
    }

    timer = al_create_timer(1.0 / 60.0);
    count = al_create_timer(1.0);
    if (!timer) {
        al_destroy_display(display);
        al_destroy_font(font);
        error("Timer creation");
    }

    queue = al_create_event_queue();
    if (!queue) {
        al_destroy_display(display);
        al_destroy_font(font);
        al_destroy_timer(timer);
        error("Event queue creation");
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    init_ships(ships);
    init_images(&turret, &crosshair);

    al_start_timer(timer);
    font = al_load_ttf_font("../Pictures/Starjedi.ttf", 18, 0);
    fontBig = al_load_ttf_font("../Pictures/Starjedi.ttf", 35, 0);
    al_hide_mouse_cursor(display);

    al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "press space to start");

    do {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            endgame = 1;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            crosshair.location_x = event.mouse.x;
            crosshair.location_y = event.mouse.y;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button & 1) {
            destroyedShips = shoot_turret(ships, crosshair, destroyedShips);
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
                    start = 1;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP && !pause) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_P:
                    pause = false;
                    break;
            }
        } else if (event.type == ALLEGRO_EVENT_TIMER && start == 1) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (!pause) {
                if (ingame == 0) {
                    display_turret(turret);
                    start_game(P1, P2, turret, font, fontBig, count);
                    spawn_ships(ships);
                    al_flush_event_queue(queue);
                    ingame = 1;
                }
                if (event.timer.source == count) {
                    if (P1.turn == true) {
                        scoreP1++;
                    } else if (P2.turn == true) {
                        scoreP2++;
                    }
                }
                display_turret(turret);
                display_ships(ships);
                move_ships(ships);
                display_timer(timer, scoreP1, scoreP2);
                al_draw_bitmap(crosshair.crosshair, crosshair.location_x, crosshair.location_y, 0);

                al_flip_display();
                if (destroyedShips == NB_SHIPS) {
                    if (P1.turn) {
                        P1.score = scoreP1;
                        P1.turn = 0;
                        P2.turn = 1;
                        ingame = 0;
                    } else if (P2.turn) {
                        P1.score = scoreP2;
                        gameover = 1;
                    }
                }
            }
        }

        if (gameover) {
            if (P1.score > P2.score) {
                P2.tickets -= 1;
                P1.tickets += 1;
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER,
                              "player 1 wins");
            } else if (P1.score < P2.score) {
                P2.tickets += 1;
                P1.tickets -= 1;
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER,
                              "player 2 wins");
            }
            endgame = 1;
        }

        if (al_is_event_queue_empty(queue)) {
            if (pause) {
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER, "pause");
            }
            al_flip_display();
        }

    } while (!endgame);

    al_destroy_bitmap(ships->explosion1);
    al_destroy_bitmap(ships->explosion2);
    al_destroy_bitmap(ships->explosion3);
    al_destroy_bitmap(ships->ship1);
    al_destroy_bitmap(ships->ship2);
    al_destroy_bitmap(ships->ship3);
    al_destroy_bitmap(turret.turretdisplay);
    al_destroy_bitmap(turret.backgrounddisplay);
    al_destroy_bitmap(crosshair.crosshair);

    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);

    return 0;
}
