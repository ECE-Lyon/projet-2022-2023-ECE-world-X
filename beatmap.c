#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beatmap.h"



int getXYTime(int difficulty, XYT tabXYT[]) {
    // get the difficulty and parses the map to play. It will return the Timing, X coord and Y coord
    FILE* file;
    switch (difficulty) {
        case 1: {
            file = fopen("../beatmaps/1meco.osu", "r");
            break;
        }
        case 2: {
            file = fopen("../beatmaps/2Luke.osu", "r");
            break;
        }
        case 3: {
            file = fopen("../beatmaps/3cantina_band.osu", "r");
            break;
        }
        case 4:{
            file = fopen("../beatmaps/4ratz.osu", "r");
        }
            break;
        case 5: {
            file = fopen("../beatmaps/10galaxy_collapse_dont_even_try_you_hear_me.osu", "r");
            break;
        }
    }
    if (!file) {
        printf("Error: could not open file\n");
        EXIT_FAILURE;
    }

    char lines[LINES];

    // read the header and ignore it, working function :D
    while (fgets(lines, sizeof(lines), file)) {
        if (strstr(lines, "[HitObjects]")) {
            break;
        }
    }

    // read the timing points, working function too :D
    while (fgets(lines + 1, sizeof(lines), file)) {
        if (lines[0] == '[') {
            break;
        }
    }

    HitObject* hitObjects = malloc(1*sizeof(HitObject));
    int nb = 0;

    // read the hit objects
    while (fgets(lines, sizeof(lines), file)) {
        HitObject ho;
        sscanf(lines, "%d,%d,%d", &ho.x, &ho.y, &ho.time);
        hitObjects = realloc(hitObjects, (++nb) * sizeof(HitObject));
        hitObjects[nb-1] = ho;
    }

    fclose(file);

    // generate circles
    for (int i = 0; i < nb; i++){
        HitObject ho = hitObjects[i];
        tabXYT[i].x = ho.x;
        tabXYT[i].y = ho.y;
        tabXYT[i].timing = ho.time;
    }



    return nb;
}

void recalculateCoords(XYT tabXYT[], int numHitObjects){
    for(int i = 0; i<numHitObjects; i++){
        tabXYT[i].x = 300+(tabXYT[i].x/2);
        tabXYT[i].y = 150+(tabXYT[i].y/2);
    }
}