#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
using namespace std;

class Joueur {
    private:
        string nom;
        char symbole;

    public:
        Joueur(string n, char s);
        string getNom() const;
        void setNom(string n);
        char getSymbole();
};

#endif