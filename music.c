//
// Created by benja on 18/04/2023.
//

#include "music.h"
void play_music(int difficulty, ALLEGRO_SAMPLE *sample) {

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
                sample = al_load_sample("../musics/music5.wav");
                break;
            case 6:
                sample = al_load_sample("../musics/music6.wav");
                break;
            case 7:
                sample = al_load_sample("../musics/music7.wav");
                break;
            case 8:
                sample = al_load_sample("../musics/music8.wav");
                break;
            case 9:
                sample = al_load_sample("../musics/music9.wav");
                break;
            case 10:
                sample = al_load_sample("../musics/music10.wav");
                break;
            default:
                fprintf(stderr, "Invalid difficulty level!\n");
                break;
        }
    if (!sample) {
        fprintf(stderr, "failed to load sample!\n");
    }
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}