#include <stdio.h>
#include <stdlib.h>
#include "ingame.h"

#define MAXHITOBJECT 5000

void removeFirst(XYT arr[], int size) {
    for (int i = 0; i < size - 1; i++) {        //i = 1906, fait lag à morttt
        arr[i] = arr[i + 1];
    }
}


void printArr(XYT arr[], int current_time, int size) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; arr[i].timing <= current_time; i++) {
        if (arr[i].timing < clock() - 100) {
            removeFirst(arr, 20);
        }
        al_draw_filled_circle(arr[i].x, arr[i].y, 10, al_map_rgb(255, 0, 0));
    }

}

void addToPrintedArr(XYT source[MAXHITOBJECT], XYT dest[20], int current_point){
    removeFirst(dest, 20);
    dest[19] = source[current_point];
}