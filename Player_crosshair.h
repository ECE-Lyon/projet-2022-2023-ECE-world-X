#ifndef PROJET_ECE_WORLD_PLAYER_CROSSHAIR_H
#define PROJET_ECE_WORLD_PLAYER_CROSSHAIR_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int location_x, location_y;
    int state;
    ALLEGRO_BITMAP *crosshair;
}Crosshair;

typedef struct {
    char name;
    float score;
    int turn;
    int tickets;
}Player;

#endif //PROJET_ECE_WORLD_PLAYER_CROSSHAIR_H
