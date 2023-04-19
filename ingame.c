//
// Created by benja on 19/04/2023.
//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "ingame.h"
#include "time.h"


void removeFromArray(XYT *array, int size){
    if (size <= 1) {
        return;
    }
    for (int i = 1; i < size; i++) {
        array[i-1] = array[i];
    }
}
void draw_circles(XYT tabXYT[], int off_beat){
    for (int i = 0; i < sizeof tabXYT; i++){
        printf("%d", tabXYT[i].timing);
        if(tabXYT[i].timing < clock()-off_beat-100){
            removeFromArray(tabXYT, sizeof tabXYT);
        }
        else {
            al_draw_filled_circle(tabXYT[i].x, tabXYT[i].y, 10, al_map_rgb(255, 0, 0));
        }
    }
}