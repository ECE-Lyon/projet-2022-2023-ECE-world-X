#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>

#include "osu/music.h"
#include "time.h"
#include "osu/ingame.h"
#include "osu/menu.h"
#include "osu/countdown.h"
#include "osu/endgame.h"
#include "osugame.h"

int main() {
    osuGame();
    return 0;
}