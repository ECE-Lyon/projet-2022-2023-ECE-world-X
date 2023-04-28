//
// Created by Félix Pignal on 19/04/2023.
//

#ifndef PROJET_CANE_H
#define PROJET_CANE_H

#include "constantes.h"

typedef struct {
    int x, y, largeur, hauteur;
    ALLEGRO_BITMAP *imageCane;
} Cane;

void drawCane(Cane* pixelCane);

void init_Cane(Cane* pixelCane);

void canePos(Cane* pixelCane, int lar, int haut) ;

void caneRepos(Cane* pixelCane);

bool cursEstDansWIND(int x, int y, Cane* pixelCane);

bool cursWind(int x, int y, int x1, int y1, int x2, int y2);

bool caneDuck(int x, int y, Cane *pixelCane);

#endif //PROJET_CANE_H
