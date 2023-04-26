//
// Created by Félix Pignal on 14/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "cane.h"
#include "constantes.h"

void init_Cane(Cane *pixelCane){
    pixelCane->imageCane = al_load_bitmap("../Images/fishingRod.png");
    if (pixelCane == NULL) {
        printf("Image doesn't load\n");
    }
}

void canePos(Cane* pixelCane, int lar, int haut) {
    pixelCane->largeur = lar;
    pixelCane->hauteur = haut;
    pixelCane->x = LARGEUR / 2 - pixelCane->largeur / 2;
    pixelCane->y = HAUTEUR / 2 - pixelCane->hauteur / 2;
}

void drawCane(Cane* pixelCane) {
    al_draw_bitmap(pixelCane->imageCane ,pixelCane->x,pixelCane->y,0);
    printf("X: %d\n\nY: %d",pixelCane->x,pixelCane->y);
}

bool cursWind(int x, int y, int x1, int y1, int x2, int y2) {
    return x >= x1 && x <= x2 && y >= y1 && y < y2;
}

bool cursEstDansWIND(int x, int y, Cane* pixelCane) {
    return cursWind(x, y, pixelCane->x, pixelCane->y, pixelCane->x+pixelCane->largeur, pixelCane->y+pixelCane->hauteur);
}