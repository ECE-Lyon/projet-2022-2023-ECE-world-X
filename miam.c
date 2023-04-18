//
// Created by trist on 05/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "miam.h"
#include "constante.h"

void init_apple(Food* pomme, Damier board) {
    int centermap;
    centermap = NBSQUARE/2;
    pomme->x = PLAYERX+(board.widthsquare*centermap);
    pomme->y = PLAYERY+(centermap*board.heightsquare);
    pomme->img = al_load_bitmap("../apple.png");
    if (pomme->img == NULL) {
        printf("Failed to load apple");
    }
}

void print_apple (Food pomme) {
    al_draw_bitmap(pomme.img, pomme.x, pomme.y, 0);
}

void coord(Food *pomme, Damier board) {
    int coordx, coordy, res;
    coordx = rand()%NBSQUARE;
    coordy = (rand()%NBSQUARE);
    coordx = PLAYERX+(board.widthsquare*coordx);
    coordy = PLAYERY+(board.heightsquare*coordy);
    pomme->x = coordx;
    pomme->y = coordy;
}
