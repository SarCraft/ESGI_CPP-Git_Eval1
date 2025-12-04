#include "Game.h"
#include "Joueur.h"
#include <iostream>

using namespace std;

Game::Game() : j1("Joueur1", 'X'), j2("Joueur2", 'O'), grid(){}

void Game::start()
{
    selectNames();
    grid.display();
    currentPlayer = &j1;
    turn();
}

void Game::selectNames()
{
    cout << "Veuillez saisir le nom du joueur 1 : ";
    string name1;
    cin >> name1;
    j1.setNom(name1);
    cout << j1.getNom() << ", votre symbole est " << j1.getSymbole() << endl;

    cout << "Veuillez saisir le nom du joueur 2 : ";
    string name2;
    cin >> name2;
    j2.setNom(name2);
    cout << j2.getNom() << ", votre symbole est " << j2.getSymbole() << endl;
}

void Game::turn()
{
    while (!grid.isFull())
    {
        cout << currentPlayer->getNom() << " Veuillez rentrer le numero de la ligne, entre 1 et 3" << endl;
        int row;
        cin >> row;
        while(row > 3 || row < 1)
        {
            cout << "Nombre incorrect, Veuillez rentrer le numero de la ligne, entre 1 et 3" << endl;
            cin >> row;
        }
        cout << currentPlayer->getNom() << " Veuillez rentrer le numero de la colonne, entre 1 et 3" << endl;
        int col;
        cin >> col;
        while(col > 3 || col < 1)
        {
            cout << "Nombre incorrect, Veuillez rentrer le numero de la colonne, entre 1 et 3" << endl;
            cin >> col;
        }
        
        // Vérifier si le placement a réussi
        if(!grid.placeSymbol(row - 1, col - 1, currentPlayer->getSymbole()))
        {
            // Si le placement a échoué, continuer la boucle sans changer de joueur
            continue;
        }

        grid.display();

        if(grid.checkWin(currentPlayer->getSymbole())){
            cout << currentPlayer->getNom() << " a remporté la partie" << endl;
            return;
        }

        if(currentPlayer == &j1)
        {
            currentPlayer = &j2;
        }else{
            currentPlayer = &j1;
        }
    }
}