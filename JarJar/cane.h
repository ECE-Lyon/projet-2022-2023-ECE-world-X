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

#endif //PROJET_CANE_H
