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
    while (grid.checkWin() == false && grid.isFull() == false)
    {
        cout << "Veuillez rentrer le numéro de la ligne" << endl;
        int row;
        cin >> row;
        cout << "Veuillez rentrer le numéro de la colonne" << endl;
        int col;
        cin >> col;
        grid.placeSymbol(row,col,currentPlayer->getSymbole());

        if(currentPlayer == &j1)
        {
            currentPlayer = &j2;
        }else{
            currentPlayer = &j1;
        }
        grid.display();
    }
}



