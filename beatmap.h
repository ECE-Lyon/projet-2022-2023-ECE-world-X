#define MAX_TIMING_POINTS 1000
#define MAX_HIT_OBJECTS 10000
#include <stdio.h>
#include <wchar.h>

typedef struct {
    int time;
    double beatLength;
    int meter;
    int sampleSet;
    int sampleIndex;
    int volume;
    int inherited;
    int kiai;
} TimingPoint;

typedef struct {
    double x;
    double y;
    int time;
    int type;
    int hitsound;
    int hitSample;
} HitObject;

TimingPoint timingPoints[MAX_TIMING_POINTS];

HitObject hitObjects[MAX_HIT_OBJECTS];

int getTimeXY(int difficulty);
void draw_map();