#include "Ship.h"
#include "Turret_and_timer.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void init_ships(Ship ships[]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        ships[i].speed = 5 + rand() % 10;
        ships[i].destroyed = 0;
        ships[i].size = (rand() % 3) + 1;
        if (ships[i].size == 1) {
            ships->ship1 = al_load_bitmap("../Pictures/ship100.png");
            ships->explosion = al_load_bitmap("../Pictures/explosion100");
            ships->width = ships->length = 100;
        } else if (ships[i].size == 2) {
            ships->ship2 = al_load_bitmap("../Pictures/ship75.png");
            ships->explosion = al_load_bitmap("../Pictures/explosion75");
            ships->width = ships->length = 75;
        } else if (ships[i].size == 3) {
            ships->ship3 = al_load_bitmap("../Pictures/ship50.png");
            ships->explosion = al_load_bitmap("../Pictures/explosion50");
            ships->width = ships->length = 50;
        }
    }
}

void spawn_ships(Ship ships[]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            ships[i].y = 10 + rand() % 350;
            if (ships[i].y >= 10 && ships[i].y <= 150) {
                ships[i].x = 10 + (rand() % (SCREEN_WIDTH - 100));
            } else if (ships[i].y > 150 && ships[i].y <= 250) {
                ships[i].x = 225 + (rand() % (SCREEN_WIDTH - 500));
            } else if (ships[i].y > 250 && ships[i].y <= 360) {
                ships[i].x = 350 + (rand() % (SCREEN_WIDTH - 750));
            }
        }
    }
}

void display_ships(Ship ships[]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            if (ships[i].size == 1) {
                al_draw_bitmap(ships->ship1, ships[i].x, ships[i].y, 0);
            } else if (ships[i].size == 2) {
                al_draw_bitmap(ships->ship2, ships[i].x, ships[i].y, 0);
            } else if (ships[i].size == 3) {
                al_draw_bitmap(ships->ship3, ships[i].x, ships[i].y, 0);
            }
        }
    }
}

