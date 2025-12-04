#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
using namespace std;

class Joueur {
    private:
        string nom;
        string symbole;

    public:
        Joueur(string n, string s);
        string getNom() const;
        void setNom(string n);
        string getSymbole() const;
};

#endif