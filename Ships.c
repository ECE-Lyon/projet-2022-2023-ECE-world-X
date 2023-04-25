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
        } else if (ships[i].size == 2) {
            ships->ship2 = al_load_bitmap("../Pictures/ship75.png");
        } else if (ships[i].size == 3) {
            ships->ship3 = al_load_bitmap("../Pictures/ship50.png");
        }
    }
}

void spawn_ships(Ship ships[]) {
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            ships[i].y = SCREEN_HEIGHT - (200 + rand() % 350);
            if (ships[i].y >= 50 && ships[i].y <= 200) {
                ships[i].x = 50 + (rand() % (SCREEN_WIDTH - 100));
            } else if (ships[i].y > 200 && ships[i].y <= 450) {
                ships[i].x = 50 + (rand() % (SCREEN_WIDTH - 400));
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

