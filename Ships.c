#include "Ship.h"
#include "Turret_and_timer.h"
#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void init_ships(Ship ships[]){
    int i = 0;
    for (i = 0; i < NB_SHIPS; i++) {
        ships[i].speed = 5 + rand() % 10;
        ships[i].destroyed = 0;
        ships[i].width = 10 + rand() % 30;
        ships[i].height = ships[i].width * 2 / 3;
    }
}

void display_ships(Ship ships[]){
    int i = 0;
    ships->ship1 = al_load_bitmap("../vaisseau1.png");
    for (i = 0; i < NB_SHIPS; i++) {
        if (ships[i].destroyed == 0) {
            al_draw_bitmap(ships->ship1, ships->x, ships->y, 0);
        }
    }
}