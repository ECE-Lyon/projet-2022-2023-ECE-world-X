#include <stdio.h>
#include <stdlib.h>
#include "ingame.h"

#define MAXHITOBJECT 5000

void removeFirst(XYT arr[], int size) {
    for(int i = 0; i+1<=size; i++){
        arr[i] = arr[i+1];
    }
}


void printArr(XYT arr[]) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); // clear display to print new circles
    int cpt = 0;
    int i;
    for (i = 0; i<20 ; i++) {
        al_draw_filled_circle(arr[i].x, arr[i].y, 10, al_map_rgb(255, 0, 0));
        cpt++;
    }
    al_flip_display();
    printf("%d\n", cpt);

    // remove points that are missed
    int j = 0;
    while (j < i && arr[j].timing < clock() - 300) { //problem here?
        removeFirst(arr, 20);
        i--;
    }
}



void addToPrintedArr(XYT source[MAXHITOBJECT], XYT dest[20], int current_point){
    removeFirst(dest, 20);
    dest[19] = source[current_point];
}