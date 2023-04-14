//
// Created by Félix Pignal on 14/04/2023.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "duck.h"
#include "constantes.h"

void duckPosition(Duck* r, int lar, int haut) {
    r->largeur = lar;
    r->hauteur = haut;
    r->x = LARGEUR / 2 - r->largeur / 2;
    r->y = HAUTEUR / 2 - r->hauteur / 2;
}

void duckReposition(Duck* r) {
    if(r->x < 0) { r->x = 0; }
    if(r->y < 0) { r->y = 0; }
    if(r->x+r->largeur > LARGEUR) { r->x = LARGEUR - r->largeur; }
    if(r->y+r->hauteur > HAUTEUR) { r->y = HAUTEUR - r->hauteur; }
}

void dessiner(Duck r) {
    al_clear_to_color(BLANC);
    al_draw_bitmap(al_load_bitmap("../Images/pixelBoat2.png"), 0,0,0);
    al_draw_bitmap(al_load_bitmap("../Images/Duck.png"),r.x,r.y,0);
    al_flip_display();
}

bool pointEstDansZone(int x, int y, int x1, int y1, int x2, int y2) {
    return x >= 0 && x <= LARGEUR && y >= 0 && y < HAUTEUR;
}

bool pointEstDansRect(int x, int y, Duck r) {
    return pointEstDansZone(x, y, r.x, r.y, r.x+r.largeur, r.y+r.hauteur);
}