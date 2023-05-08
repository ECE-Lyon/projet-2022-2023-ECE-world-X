//
// Created by trist on 23/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constante.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "character.h"


#ifndef PROJET_BACKGROUND_H
#define PROJET_BACKGROUND_H

typedef struct {
    int x, y;
    ALLEGRO_BITMAP* img;
}Background;

void init_bg (Background* bar);
void print_background(Background bar);
void move_bg(Background* bar, int Keys[NBKEYS]);
void square_ticket (ALLEGRO_FONT* police, Perso player1, Perso player2, ALLEGRO_BITMAP* ticket);

#endif //PROJET_BACKGROUND_H
