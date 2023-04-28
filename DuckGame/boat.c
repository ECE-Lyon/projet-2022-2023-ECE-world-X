//
// Created by Félix Pignal on 19/04/2023.
//
#include "constantes.h"

void init_boat(Boat* smallBoat){
   smallBoat -> boaty = al_load_bitmap("../Images/pixelBoat.png");;
   smallBoat -> x = 40;
   smallBoat -> y = 20;
   smallBoat -> score = 0;
}

void printBoat(Boat* smallBoat){
    al_draw_bitmap(smallBoat -> boaty, smallBoat -> x,smallBoat -> y,0);
}
void counterBoat(Boat* smallBoat){

}
