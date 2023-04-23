//
// Created by trist on 23/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "constante.h"


#ifndef PROJET_BACKGROUND_H
#define PROJET_BACKGROUND_H

typedef struct {
    int x,y;
    ALLEGRO_BITMAP* img;
}Background;

void init_bg (Background* bar);
void print_background(Background bar);
void move_bg(Background* bar, int Keys[NBKEYS]);

#endif //PROJET_BACKGROUND_H
