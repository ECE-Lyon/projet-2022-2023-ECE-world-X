#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "beatmap.h"
int getTimeXY(int difficulty){
    // get the difficulty and parses the map to play. It will return the Timing, X coord and Y coord
    int numHitObjects = 0;
    int numTimingPoints = 0;
    FILE* file;
    switch (difficulty) {
        case 1: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/1castle_of_glass.osu", "r");
            break;
        }
        case 2: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/2pokemon.osu", "r");
            break;
        }
        case 3: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/3canon_rock.osu", "r");
            break;
        }
        case 4:{
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/4ratz.osu", "r");
        }
            break;
        case 5: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/5faith.osu", "r");
            break;
        }
        case 6: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/6through_the_fire_and_flames.osu", "r");
            break;
        }
        case 7: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/7embraced_by_the_flames.osu", "r");
            break;
        }
        case 8: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/8happpy_song_dont_play_that_too_harddd.osu", "r");
            break;
        }
        case 9: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/9a_fool_moon_night_aaaaaaahhhhhhhh.osu", "r");
            break;
        }
        case 10: {
            file = fopen("C:/Users/benja/CLionProjects/osu/beatmaps/10galaxy_collapse_dont_even_try_you_hear_me.osu", "r");
            break;
        }
    }
    if (!file) { //on doit changer le chemin absolu
        printf("Error: could not open file\n");
        return 1;
    }

    char lines[1024];

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
        TimingPoint tp;
        sscanf(lines, "%d,%lf,%d,%d,%d,%d,%d,%d",
               &tp.time, &tp.beatLength, &tp.meter, &tp.sampleSet,
               &tp.sampleIndex, &tp.volume, &tp.inherited, &tp.kiai);
        timingPoints[numTimingPoints++] = tp;
    }

    // read the hit objects
    while (fgets(lines, sizeof(lines), file)) {
        HitObject ho;
        sscanf(lines, "%lf,%lf,%d,%d,%d,%d:%*[^:]", &ho.x, &ho.y, &ho.time, &ho.type, &ho.hitsound, &ho.hitSample);
        if (ho.type == 1) {
            hitObjects[numHitObjects++] = ho;
        }
    }

    fclose(file);

    // generate circles
    printf("NUM : %d\n", numHitObjects);
    for (int i = 0; i < numHitObjects; i++) {
        HitObject ho = hitObjects[i];
        int closestTimingPoint = -1;
        double minDistance = INFINITY;
        for (int j = 0; j < numTimingPoints; j++) {
            TimingPoint tp = timingPoints[j];
            double distance = fabs(ho.time - tp.time);
            if (distance < minDistance) {
                closestTimingPoint = j;
                minDistance = distance;
            }
        }
        printf("%d,%lf,%lf\n", ho.time, ho.x, ho.y);
    }
}
