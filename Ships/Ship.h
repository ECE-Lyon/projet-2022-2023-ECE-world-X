#ifndef PROJET_ECE_WORLD_SHIP_H
#define PROJET_ECE_WORLD_SHIP_H

#include "const.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int x, y;
    int width, length;
    int size;
    int speed;
    bool destroyed;
    ALLEGRO_BITMAP *ship1, *ship2, *ship3;
    ALLEGRO_BITMAP *explosion1, *explosion2, *explosion3;
} Ship;

void init_ships(Ship ships[NB_SHIPS]);

void display_ships(Ship ships[NB_SHIPS]);

void move_ships(Ship ships[NB_SHIPS]);

void spawn_ships(Ship ships[NB_SHIPS]);

#endif //PROJET_ECE_WORLD_SHIP_H
