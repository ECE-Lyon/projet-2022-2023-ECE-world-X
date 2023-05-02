//
// Created by Félix Pignal on 14/04/2023.
//

#include "constantes.h"

void init_Cane(Cane *pixelCane){
    pixelCane->imageCane = al_load_bitmap("../Images/fishingRod.png");;
}

void canePos(Cane* pixelCane, int lar, int haut) {
    pixelCane->largeur = lar;
    pixelCane->hauteur = haut;
    pixelCane->x = LARGEUR / 2 - pixelCane->largeur / 2;
    pixelCane->y = HAUTEUR / 2 - pixelCane->hauteur / 2;
}

void drawCane(Cane* pixelCane) {
    al_draw_bitmap(pixelCane->imageCane ,pixelCane->x,pixelCane->y,0);
}