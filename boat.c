//
// Created by Félix Pignal on 19/04/2023.
//
#include "constantes.h"
#include "boat.h"

void init_boat(Boat* smallBoat){
   smallBoat -> boaty = al_load_bitmap("../Images/pixelBoat.png");
   smallBoat -> x = 975;
   smallBoat -> y = 950;
   smallBoat -> h = al_get_bitmap_height(smallBoat->boaty);
   smallBoat -> l = al_get_bitmap_width(smallBoat->boaty);
   smallBoat -> score = 0;
}

void printBoat(Boat* smallBoat){
    al_draw_bitmap(smallBoat -> boaty, smallBoat -> x,smallBoat -> y,0);
}
