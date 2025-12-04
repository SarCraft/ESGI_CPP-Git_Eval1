#ifndef ESGI_CPP_GIT_EVAL1_PVP_H
#define ESGI_CPP_GIT_EVAL1_PVP_H

#include "Joueur.h"
#include "Grid.h"


class Pvp
{
    private:
        Joueur j1;
        Joueur j2;
        Joueur* currentPlayer;
        Grid grid;


    public:
        Pvp();
        void turn();
        void start();
        void selectNames();
};

#endif //ESGI_CPP_GIT_EVAL1_PVP_H
