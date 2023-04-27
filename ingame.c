#include <stdio.h>
#include <stdlib.h>
#include "ingame.h"

#define MAXHITOBJECT 5000
#define MAX_TIMING 1000000000

void removeFirst(XYT arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1].x = 0;
    arr[size - 1].y = 0;
    arr[size - 1].timing = MAX_TIMING;
}


void printArr(XYT arr[]) {
    int i;
    for (i = 0; i < 20; i++) {
        if (arr[i].timing != 0) {
            al_draw_filled_circle(arr[i].x, arr[i].y, 10, al_map_rgb(255, 0, 0));
        }
    }
    al_flip_display();

    // remove points that are missed
    int j = 0;
    while (j < i && arr[j].timing < clock() - 500) {
        for (; j < 20 - 1; j++) {
            arr[j] = arr[j + 1];
        }
        i--;
    }
}


void addToPrintedArr(XYT source[], XYT dest[], int current_point) {
    dest[19].x = source[current_point].x;
    dest[19].y = source[current_point].y;
    dest[19].timing = source[current_point].timing;
    shiftLeft(dest);
}

void shiftLeft(XYT arr[]) {
    for (int i = 0; i < 20 - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[20 - 1].x = 0;
    arr[20 - 1].y = 0;
    arr[20 - 1].timing = 0;

}