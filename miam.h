//
// Created by trist on 05/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef PROJET_MIAM_H
#define PROJET_MIAM_H

typedef struct {
    int x, y;
    ALLEGRO_BITMAP* img;
}Food;

void print_apple (Food pomme);
void init_apple(Food* pomme, int wisquare, int heisquare);
void coord(Food* pomme,int wisquare, int heisquare);

#endif //PROJET_MIAM_H
