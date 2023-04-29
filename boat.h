//
// Created by Félix Pignal on 19/04/2023.
//

#ifndef PROJET_BOAT_H
#define PROJET_BOAT_H

typedef struct {
    int x, y, h, l;
    int score;
    ALLEGRO_BITMAP *boaty;
} Boat;

void printBoat(Boat* smallBoat);

void init_boat(Boat* smallBoat);



#endif //PROJET_BOAT_H
