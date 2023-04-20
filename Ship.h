#ifndef PROJET_ECE_WORLD_SHIP_H
#define PROJET_ECE_WORLD_SHIP_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int x, y;
    int size;
    int speed;
    bool destroyed;
    ALLEGRO_BITMAP *ship1, *ship2, *ship3;
    ALLEGRO_BITMAP *explosion;
}Ship;

void init_ships(Ship ships[]);

void display_ships(Ship ships[]);

void move_ships(Ship ships[]);

void spawn_ships(Ship ships[]);

#endif //PROJET_ECE_WORLD_SHIP_H
