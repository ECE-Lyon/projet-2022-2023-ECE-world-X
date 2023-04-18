//
// Created by Félix Pignal on 18/04/2023.
//
void init_ennemis(Ennemi ennemis[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        ennemis[i].vitesse = 2 + rand() % 3;
        ennemis[i].actif = 0;
        ennemis[i].width = 10 + rand() % 20;
        ennemis[i].height = ennemis[i].width * 2 / 3;
    }
}

void affiche_ennemis(Ennemi ennemis[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ennemis[i].actif) {
            al_draw_filled_ellipse(ennemis[i].x, ennemis[i].y, ennemis[i].width, ennemis[i].height,
                                   al_map_rgb(255, 100 + rand() % 156, 100 + rand() % 156));
        }
    }
}

void mouvement_ennemis(Ennemi ennemis[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (ennemis[i].actif) {
            ennemis[i].x -= ennemis[i].vitesse;
            if (ennemis[i].x - ennemis[i].width < 0) {
                ennemis[i].actif = 0;
            }
        }
    }
}

void apparition_ennemis(Ennemi ennemis[]) {
    int i = 0;
    for (i = 0; i < NB_MAX_ENNEMIS; i++) {
        if (!ennemis[i].actif && rand() % 1000 < 10) {
            ennemis[i].x = SCREEN_WIDTH - ennemis[i].width;
            ennemis[i].y = ennemis[i].height + rand() % (SCREEN_HEIGHT - (ennemis[i].height * 2));
            ennemis[i].actif = 1;
        }
    }
}