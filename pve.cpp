#include "Joueur.h"
#include "pve.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

Pve::Pve() : j1("Joueur1", 'X'), bot("bot", 'O'), grid(){}

void Pve::start()
{
    selectNames();
    grid.display();
    currentPlayer = &j1;
    turn();
}

void Pve::selectNames()
{
    cout << "Veuillez saisir le nom du joueur 1 : ";
    string name1;
    cin >> name1;
    j1.setNom(name1);
    cout << j1.getNom() << ", votre symbole est " << j1.getSymbole() << endl;

    cout << bot.getNom() << " a comme symbole : " << bot.getSymbole() << endl;
}

void Pve::turn()
{
    // initialiser le random une seule fois
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }

    while (!grid.isFull())
    {
        int row;
        int col;

        if (currentPlayer == &j1)
        {
            // ----- TOUR DU JOUEUR HUMAIN -----
            cout << currentPlayer->getNom() << " Veuillez rentrer le numero de la ligne, entre 1 et 3" << endl;
            cin >> row;
            while(cin.fail() || row > 3 || row < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrée incorrect, Veuillez rentrer le numero de la ligne, entre 1 et 3" << endl;
                cin >> row;
            }

            cout << currentPlayer->getNom() << " Veuillez rentrer le numero de la colonne, entre 1 et 3" << endl;
            cin >> col;
            while(cin.fail() || col > 3 || col < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrée incorrect, Veuillez rentrer le numero de la colonne, entre 1 et 3" << endl;
                cin >> col;
            }

            if (!grid.placeSymbol(row - 1, col - 1, currentPlayer->getSymbole()))
            {
                continue;
            }
        }
        else
        {
            cout << "Tour du bot..." << endl;
            while (!grid.placeSymbol(row, col, currentPlayer->getSymbole())){
                row = rand() % 3; // 0,1 ou 2
                col = rand() % 3; // 0,1 ou 2
            }

            cout << "Le bot a joué en ligne :  " << row + 1 << " et colonne : " << col + 1 << endl;
        }

        grid.display();

        if (grid.checkWin(currentPlayer->getSymbole())) {
            cout << currentPlayer->getNom() << " a remporté la partie" << endl;
            return;
        }

        if (grid.isFull()) {
            cout << "Egalité !" << endl;
            grid.reset();
            return;
        }

        if (currentPlayer == &j1)
        {
            currentPlayer = &bot;
        }
        else
        {
            currentPlayer = &j1;
        }
    }
}
