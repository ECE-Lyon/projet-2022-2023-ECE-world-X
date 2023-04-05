//
// Created by trist on 05/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "miam.h"
#include "constante.h"

void init_apple(Food* pomme, int wisquare, int heisquare) {
    int centermap;
    centermap = NBSQUARE/2;
    pomme->x = PLAYERX+(wisquare*centermap);
    pomme->y = PLAYERY+(centermap*heisquare);
    pomme->img = al_load_bitmap("/Users/trist/OneDrive/Documents/CoursECE/CLionProjects/projet2minijeux/projet-2022-2023-ECE-world-X/apple.png");
    if (pomme->img == NULL) {
        printf("Failed to load apple");
    }
}

void print_apple (Food pomme) {
    al_draw_bitmap(pomme.img, pomme.x, pomme.y, 0);
    al_flip_display();
}

void coord(Food *pomme,int wisquare, int heisquare) {
    int coordx, coordy;
    coordx = rand()%NBSQUARE;
    coordy = (rand()%NBSQUARE);
    coordx = PLAYERX+(wisquare*coordx);
    coordy = PLAYERY+(heisquare*coordy);
    pomme->x = coordx;
    pomme->y = coordy;
}
