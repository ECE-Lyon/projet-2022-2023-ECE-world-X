
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
#include "../Map/character.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int game_ships(ALLEGRO_DISPLAY* display, Perso* player1, Perso* player2) {
    int endgame = 0, gameover = 0, pause = 0, destroyed_Ships = 0, start = 0, ingame = 0, scoreP1 = 0, scoreP2 = 0;
    FPSdisplay turret;
    Ship ships[NB_SHIPS];
    Crosshair crosshair;
    Player P1;
    P1.name = 22;
    P1.turn = true;
    Player P2;
    P2.name = 23;
    P2.turn = false;

    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *fontBig = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_SAMPLE* themeship = al_load_sample("../Ships/themeship.wav");
    assert(themeship);
    timer = al_create_timer(1.0 / 60.0);

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

    init_images(&turret, &crosshair);

    al_start_timer(timer);
    al_play_sample(themeship, 1,0,1,ALLEGRO_PLAYMODE_LOOP,0);

    font = al_load_ttf_font("../Ships/Pictures/Starjedi.ttf", 18, 0);
    fontBig = al_load_ttf_font("../Ships/Pictures/Starjedi.ttf", 35, 0);
    al_hide_mouse_cursor(display);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
    al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
    al_draw_text(fontBig, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - al_get_font_ascent(fontBig), ALLEGRO_ALIGN_CENTER, "press space to start");

    do {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            endgame = 1;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            crosshair.location_x = event.mouse.x;
            crosshair.location_y = event.mouse.y;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            switch (event.mouse.button) {
                case 1:
                    shoot_turret(ships, crosshair);
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
            if (event.timer.source == timer) {
                al_clear_to_color(al_map_rgb(0, 0, 0));

                if (!pause) {
                    if (ingame == 0) {
                        display_turret(turret);
                        start_game(P1, P2, turret, font, fontBig, *player1, *player2);
                        init_ships(ships);
                        spawn_ships(ships);
                        al_flush_event_queue(queue);
                        ingame = 1;
                    }
                    display_turret(turret);
                    display_ships(ships);
                    move_ships(ships);
                    al_draw_bitmap(crosshair.crosshair, crosshair.location_x, crosshair.location_y, 0);
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 30,
                                  520 - al_get_font_ascent(font), 0, "score joueur 1: %d", scoreP1);
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 30,
                                  545 - al_get_font_ascent(font), 0, "score joueur 2: %d", scoreP2);
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 940,
                                  525 - al_get_font_ascent(font), 0, "vaisseaux détruits : %d", destroyed_Ships);
                    al_flip_display();

                    destroyed_Ships =
                            ships[0].destroyed + ships[1].destroyed + ships[2].destroyed + ships[3].destroyed +
                            ships[4].destroyed + ships[5].destroyed + ships[6].destroyed + ships[7].destroyed +
                            ships[8].destroyed + ships[9].destroyed + ships[10].destroyed + ships[11].destroyed +
                            ships[12].destroyed + ships[13].destroyed + ships[14].destroyed +
                            ships[15].destroyed + ships[16].destroyed + ships[17].destroyed +
                            ships[18].destroyed + ships[19].destroyed + ships[20].destroyed +
                            ships[21].destroyed + ships[22].destroyed + ships[23].destroyed + ships[24].destroyed;
                    if (destroyed_Ships == NB_SHIPS) {
                        if (P1.turn == true) {
                            player1->score = scoreP1;
                            P1.score = scoreP1;
                            P1.turn = false;
                            P2.turn = true;
                            destroyed_Ships = 0;
                            ingame = 0;
                        } else if (P2.turn == true) {
                            player2->score = scoreP2;
                            P2.score = scoreP2;
                            gameover = 1;
                        }
                    }
                    if (event.timer.count % 60 == 0) {
                        if (P1.turn == true) {
                            scoreP1++;
                        } else if (P2.turn == true) {
                            scoreP2++;
                        }
                    }
                }
            }
        }

        if (gameover) {
            if (P1.score < P2.score) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
                al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER,
                              "%s wins", player1->name);
                player2->ticket--;
                al_flip_display();
                al_rest(2);
            } else if (P1.score > P2.score) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
                al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER,
                              "%s wins", player2->name);
                al_flip_display();
                player1->ticket--;
                al_rest(2);
            }
            else if (P1.score == P2.score) {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(turret.backgrounddisplay, 0, 0, 0);
                al_draw_bitmap(turret.turretdisplay, 0, 159, 0);
                al_draw_text(font, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
                             SCREEN_HEIGHT / 2 - al_get_font_ascent(font), ALLEGRO_ALIGN_CENTER,
                             "draw");
                al_flip_display();
                player1->ticket--;
                player2->ticket--;
                al_rest(2);
            }
            endgame = true;
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

    al_destroy_bitmap(ships->explosion1);
    al_destroy_bitmap(ships->explosion2);
    al_destroy_bitmap(ships->explosion3);
    al_destroy_bitmap(ships->ship1);
    al_destroy_bitmap(ships->ship2);
    al_destroy_bitmap(ships->ship3);
    al_destroy_bitmap(turret.turretdisplay);
    al_destroy_bitmap(turret.backgrounddisplay);
    al_destroy_bitmap(crosshair.crosshair);
    al_destroy_sample(themeship);
    al_destroy_font(font);
    al_destroy_font(fontBig);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);


    return 0;
}