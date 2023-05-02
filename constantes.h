//
// Created by Félix Pignal on 14/04/2023.
//

#ifndef PROJET_CONSTANTES_H
#define PROJET_CONSTANTES_H

#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <assert.h>
#include "Duck.h"
#include "cane.h"
#include "boat.h"
#include "duckGame.h"


#define BTN_LEFT 1
#define LARGEUR 1200*2
#define HAUTEUR 600*2
#define HAUTEURMAX 500*2
#define BLEU al_map_rgb(128, 197, 222)
#define NOIR al_map_rgb(0,0,0)
#define JAUNE al_map_rgb(255,232,31)
#define FPS 60.0

#endif //PROJET_CONSTANTES_H
