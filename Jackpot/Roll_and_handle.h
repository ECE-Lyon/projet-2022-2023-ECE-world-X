

#ifndef MAIN_C_ROLL_AND_HANDLE_H
#define MAIN_C_ROLL_AND_HANDLE_H

#include "../Map/character.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    int rotation_speed;
    int location_x;
    ALLEGRO_BITMAP *Picture1, *Picture2, *Picture3, *Picture4, *Picture5, *Picture6, *Picture7, *Picture8, *Picture9;
} Roll;

typedef struct {
    bool down;
    ALLEGRO_BITMAP *Machine_up, *Machine_down;
} Handle;

void error(const char *txt);

void init_images(Roll roll[], Handle handle);

int prize(Roll roll[], Perso P1);

void display_rolls(Roll roll[]);

void display_Machine(Handle handle);

#endif //MAIN_C_ROLL_AND_HANDLE_H
