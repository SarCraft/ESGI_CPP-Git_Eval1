#include "Game.h"
#include "pvp.h"
#include "pve.h"
#include <iostream>

using namespace std;

void Game::start()
{
    Pvp pvp;
    Pve pve;


    int modeJeu;
    cout << "Choisissez votre mode de jeu : 1 = 1_Joueur, 2 = 2_Joueurs" <<endl;
    cin >> modeJeu;
    switch (modeJeu) {
        case 1:
            pve.start();
            break;
        case 2:
            pvp.start();
            break;
        default:
            cout << "Entree invalide" << endl;
            break;
    }
}
