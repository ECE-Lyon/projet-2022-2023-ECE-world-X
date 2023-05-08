//
// Created by Félix Pignal on 19/04/2023.
//
#include "constantes.h"
#include "boat.h"


void init_boat(Boat* smallBoat){
   smallBoat -> boaty = al_load_bitmap("../JarJar/Images/pixelBoat.png");
   smallBoat -> x = LARGEUR/2;// valeur reste consante pour toute machine et utilisateurs
   smallBoat -> y = HAUTEUR - al_get_bitmap_height(smallBoat->boaty);
   smallBoat -> h = al_get_bitmap_height(smallBoat->boaty);// une hauter fixe definis par la taille de l'image
   smallBoat -> l = al_get_bitmap_width(smallBoat->boaty);
   smallBoat -> score = 0;// le bateau est celui a stocker le score
   smallBoat -> frame = 0;
   smallBoat -> fps = 0;
   smallBoat -> actif =1;
}

void printBoat(Boat* smallBoat){
    al_draw_bitmap(smallBoat -> boaty, smallBoat -> x,smallBoat -> y,ALLEGRO_FLIP_HORIZONTAL);
}

