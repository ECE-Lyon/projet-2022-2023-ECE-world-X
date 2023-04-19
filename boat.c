//
// Created by Félix Pignal on 19/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <assert.h>
#include "constantes.h"
#include "boat.h"

void init_boat(Boat* smallBoat){
   smallBoat -> boaty =  al_load_bitmap("../Images/pixelBoat.png");
   smallBoat -> x = 40;
   smallBoat -> y = 20;
}

void printBoat(Boat* smallBoat){
    al_draw_bitmap(smallBoat -> boaty, smallBoat -> x,smallBoat -> y,0);
}