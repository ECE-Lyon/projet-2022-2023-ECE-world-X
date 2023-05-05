#define MAX_TIMING_POINTS 10000
#define MAX_HIT_OBJECTS 10000
#define MAX_POINTS 3000
#define LINES 1024
#define MAXHITOBJECT 5000

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
    int x;
    int y;
    int time;
    int type;
    int hitsound;
    int hitSample;
} HitObject;

typedef struct {
    int x;
    int y;
    int timing;
} XYT;


TimingPoint timingPoints[MAX_TIMING_POINTS];


int getXYTime(int difficulty, XYT tab[MAXHITOBJECT]);

void recalculateCoords(XYT tab[], int numHitObjects);