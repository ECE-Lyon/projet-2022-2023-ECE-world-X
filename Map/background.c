//
// Created by trist on 23/04/2023.
//

#include "background.h"
#include "constante.h"

#include <stdio.h>

void init_bg (Background* bar) {
    bar->x = BGX;
    bar->y = BGY;
    bar->img = al_load_bitmap("../Map/mapv2large.png");
    if (bar->img == NULL) {
        printf("Failed to load Background\n");
    }
}

void print_background(Background bar) {
    al_draw_bitmap(bar.img, bar.x, bar.y, 0);
}

void move_bg(Background* bar, int Keys[NBKEYS]) {
    bar->x -= SPEEDBG*Keys[DROITE];
    bar->x += SPEEDBG*Keys[GAUCHE];
    bar->y += SPEEDBG*Keys[HAUT];
    bar->y -= SPEEDBG*Keys[BAS];
}