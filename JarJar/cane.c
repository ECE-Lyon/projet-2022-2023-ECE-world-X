//
// Created by Félix Pignal on 14/04/2023.
//

#include "constantes.h"
#include "cane.h"

void init_Cane(Cane *pixelCane){
    pixelCane->imageCane = al_load_bitmap("../JarJar/Images/fishingRod.png");;
}

void drawCane(Cane* pixelCane) {
    al_draw_bitmap(pixelCane->imageCane ,pixelCane->x,pixelCane->y,0);
}