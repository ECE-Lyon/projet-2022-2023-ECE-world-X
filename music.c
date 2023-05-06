#include "music.h"

ALLEGRO_SAMPLE_INSTANCE *play_music(int difficulty) {
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *sampleInstance = NULL;

    switch (difficulty) {
        case 1:
            sample = al_load_sample("../musics/music1.wav");
            break;
        case 2:
            sample = al_load_sample("../musics/music2.wav");
            break;
        case 3:
            sample = al_load_sample("../musics/music3.wav");
            break;
        case 4:
            sample = al_load_sample("../musics/music4.wav");
            break;
        case 5:
            sample = al_load_sample("../musics/music10.wav");
            break;
        default:
            fprintf(stderr, "Invalid difficulty level!\n");
            break;
    }

    if (!sample) {
        fprintf(stderr, "failed to load sample!\n");
        return NULL;
    }

    sampleInstance = al_create_sample_instance(sample);
    if (!sampleInstance) {
        fprintf(stderr, "failed to create sample instance!\n");
        al_destroy_sample(sample);
        return NULL;
    }

    al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());

    al_play_sample_instance(sampleInstance);

    return sampleInstance;
}
