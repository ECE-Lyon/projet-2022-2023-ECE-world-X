#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "beatmap.h"



int getXYTime(int difficulty, XYT tabXYT[]) {
    // get the difficulty and parses the map to play. It will return the Timing, X coord and Y coord
    int numHitObjects = 0;
    int numTimingPoints = 0;
    FILE* file;
    switch (difficulty) {
        case 1: {
            file = fopen("../beatmaps/1castle_of_glass.osu", "r");
            break;
        }
        case 2: {
            file = fopen("../beatmaps/2pokemon.osu", "r");
            break;
        }
        case 3: {
            file = fopen("../beatmaps/3canon_rock.osu", "r");
            break;
        }
        case 4:{
            file = fopen("../beatmaps/4ratz.osu", "r");
        }
            break;
        case 5: {
            file = fopen("../beatmaps/5faith.osu", "r");
            break;
        }
        case 6: {
            file = fopen("../beatmaps/6through_the_fire_and_flames.osu", "r");
            break;
        }
        case 7: {
            file = fopen("../beatmaps/7embraced_by_the_flames.osu", "r");
            break;
        }
        case 8: {
            file = fopen("../beatmaps/8happpy_song_dont_play_that_too_harddd.osu", "r");
            break;
        }
        case 9: {
            file = fopen("../beatmaps/9a_fool_moon_night_aaaaaaahhhhhhhh.osu", "r");
            break;
        }
        case 10: {
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
    printf("NUM : %d\n", nb);
    for (int i = 0; i < nb; i++){
        HitObject ho = hitObjects[i];
        tabXYT[i].x = ho.x;
        tabXYT[i].y = ho.y;
        tabXYT[i].timing = ho.time;
        printf("%d, %d, %d\n", tabXYT[i].x, tabXYT[i].y, tabXYT[i].timing);
    }



    return nb;
}