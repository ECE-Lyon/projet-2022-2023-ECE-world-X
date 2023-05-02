#include "Ship.h"
#include "Start_and_images.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void init_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        ships[i].speed = 1 + rand() % 10;
        ships[i].destroyed = 0;
        ships[i].size = (rand() % 3) + 1;
        if (ships[i].size == 1) {
            ships->ship1 = al_load_bitmap("../Pictures/ship100.png");
            ships->explosion1 = al_load_bitmap("../Pictures/explosion100");
            ships->width = ships->length = 100;
        } else if (ships[i].size == 2) {
            ships->ship2 = al_load_bitmap("../Pictures/ship75.png");
            ships->explosion2 = al_load_bitmap("../Pictures/explosion75");
            ships->width = ships->length = 75;
        } else if (ships[i].size == 3) {
            ships->ship3 = al_load_bitmap("../Pictures/ship50.png");
            ships->explosion3 = al_load_bitmap("../Pictures/explosion50");
            ships->width = ships->length = 50;
        }
    }
}

void spawn_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            ships[i].y = 10 + rand() % (400 - ships[i].length);
            if (ships[i].y >= 10 && ships[i].y <= 185) {
                ships[i].x = 65 + (rand() % (SCREEN_WIDTH - (65 + ships[i].width)));
            } else if (ships[i].y > 185 && ships[i].y <= 335) {
                ships[i].x = 250 + (rand() % (SCREEN_WIDTH - (250 + ships[i].width)));
            } else if (ships[i].y > 335 && ships[i].y <= 410) {
                ships[i].x = 350 + (rand() % (SCREEN_WIDTH - (350 + ships[i].width)));
            }
        }
    }
}

void display_ships(Ship ships[NB_SHIPS]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            if (ships[i].y >= 10 && ships[i].y <= (185 - ships[i].length) && ships[i].x >= 65 &&
                ships[i].x <= (1135 - (ships[i].width + ships[i].width))) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            } else if (ships[i].y > 185 && ships[i].y <= (335 - ships[i].length) && ships[i].x >= 250 &&
                       ships[i].x <= (950 - (ships[i].width + ships[i].width))) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            } else if (ships[i].y > 335 && ships[i].y <= (410 - ships[i].length) && ships[i].x >= 350 &&
                       ships[i].x <= (850 - (ships[i].width + ships[i].width))) {
                if (ships[i].size == 1) {
                    al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 2) {
                    al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
                } else if (ships[i].size == 3) {
                    al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
                }
            } else{
                printf("b");
            }
        }
    }
}

void move_ships(Ship ships[NB_SHIPS]) {
    srand(time(NULL));
    int i = 0;
    int direction = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            direction = rand() % 4;
            switch (direction) {
                case 0:
                    ships[i].y -= ships[i].speed;
                    break;
                case 1:
                    ships[i].y += ships[i].speed;
                    break;
                case 2:
                    ships[i].x -= ships[i].speed;
                    break;
                case 3:
                    ships[i].x += ships[i].speed;
                    break;
            }
            if (ships[i].x < 65 && ships[i].y > 10 && ships[i].y < 185) {
                ships[i].x = 1135 - ships[i].width;

            } else if (ships[i].x > (1135 - ships[i].width) && ships[i].y > 10 && ships[i].y < 185) {
                ships[i].x = 65;

            } else if (ships[i].x < 250 && ships[i].y > 185 && ships[i].y < 335) {
                ships[i].x = 950 - ships[i].width;

            } else if (ships[i].x > (950 - ships[i].width) && ships[i].y > 185 && ships[i].y < 335) {
                ships[i].x = 250;

            } else if (ships[i].x < 350 && ships[i].y > 335 && ships[i].y < 410) {
                ships[i].x = 850 - ships[i].width;

            } else if (ships[i].x > (850 - ships[i].width) && ships[i].y > 335 && ships[i].y < 410) {
                ships[i].x = 350;

            } else if (ships[i].y < 10) {
                if (ships[i].x > 65 && ships[i].x < 250) {
                    ships[i].y = 185;

                } else if (ships[i].x<(1135 - ships[i].width) && ships[i].x>(950 - ships[i].width)) {
                    ships[i].y = 185;

                } else if (ships[i].x > 250 && ships[i].x < 350) {
                    ships[i].y = 335;

                } else if (ships[i].x<(950 - ships[i].width) && ships[i].x>(850 - ships[i].width)) {
                    ships[i].y = 335;

                } else if (ships[i].x > 350 && ships[i].x < 850) {
                    ships[i].y = 410;

                }

            } else if (ships[i].y > 185 && ships[i].x > 65 && ships[i].x < 250) {
                ships[i].y = 10;

            } else if (ships[i].y > 185 && ships[i].x<(1135 - ships[i].width) && ships[i].x>(950 - ships[i].width)) {
                ships[i].y = 10;

            } else if (ships[i].y > 335 && ships[i].x > 250 && ships[i].x < 350) {
                ships[i].y = 10;

            } else if (ships[i].y > 335 && ships[i].x<(950 - ships[i].width) && ships[i].x>(850 - ships[i].width)) {
                ships[i].y = 10;

            } else if (ships[i].y > 410 && ships[i].x > 350 && ships[i].x < 850) {
                ships[i].y = 10;

            }
        }
    }
}