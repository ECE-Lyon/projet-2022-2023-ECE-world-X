//
// Created by Félix Pignal on 19/04/2023.
//

#ifndef PROJET_CANE_H
#define PROJET_CANE_H

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <assert.h>

typedef struct {
    int x, y, largeur, hauteur;
    ALLEGRO_BITMAP *imageCane;
} Cane;

void drawCane(Cane* pixelCane);

void init_Cane(Cane* pixelCane);

void canePos(Cane* pixelCane, int lar, int haut) ;

void caneRepos(Cane* pixelCane);

bool pointEstDansZone(int x, int y, int x1, int y1, int x2, int y2);

bool pointEstDansRect(int x, int y, Cane* pixelCane);

#endif //PROJET_CANE_H
