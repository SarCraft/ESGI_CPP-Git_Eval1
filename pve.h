#ifndef ESGI_CPP_GIT_EVAL1_PVE_H
#define ESGI_CPP_GIT_EVAL1_PVE_H

#include "Joueur.h"
#include "Grid.h"


class Pve
{
    private:
        Joueur j1;
        Joueur bot;
        Joueur* currentPlayer;
        Grid grid;


    public:
        Pve();
        void turn();
        void start();
        void selectNames();
};

#endif //ESGI_CPP_GIT_EVAL1_PVE_H
