#include <stdio.h>
#include <stdlib.h>
#include "ingame.h"

#define MAXHITOBJECT 5000

void removeFirst(XYT arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
}


void printArr(XYT arr[], int current_time, int size){
    for (int i = 0; arr[i].timing<=current_time; i++){
        al_draw_filled_circle(arr[i].x, arr[i].y, 10, al_map_rgb(255, 0, 0));
        al_flip_display();
        if (arr[i].timing < clock()-100){
            removeFirst(arr, size);
        }
    }

}