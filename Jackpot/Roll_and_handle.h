#ifndef MAIN_C_ROLL_AND_HANDLE_H
#define MAIN_C_ROLL_AND_HANDLE_H

#include "../Map/character.h"
#include "const_jackpot.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef struct {
    float rotation_speed;
    int location_x;
    int order[9];
    float y1, y2, y3, y4, y5, y6, y7, y8, y9;
    ALLEGRO_BITMAP *Picture1, *Picture2, *Picture3, *Picture4, *Picture5, *Picture6, *Picture7, *Picture8, *Picture9;
} Roll;

typedef struct {
    bool down;
    ALLEGRO_BITMAP *Machine_up, *Machine_down, *Machine_background;
} Handle;
//
int game_jackpot();

void error_jackpot(const char *txt);

void init_images_jackpot(Roll roll[NB_ROLLS], Handle *handle);

int prize(Roll roll[NB_ROLLS], Perso P1);

void rolling(Roll roll[NB_ROLLS], float acceleration, float max_speed);

void init_rolls(Roll roll[NB_ROLLS]);

void display_rolls(Roll roll[NB_ROLLS]);

void display_Machine(Handle handle, ALLEGRO_FONT *font);

void display_background( Handle handle);

#endif //MAIN_C_ROLL_AND_HANDLE_H