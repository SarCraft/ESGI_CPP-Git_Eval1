#include "Joueur.h"

Joueur::Joueur(string n, string s) : nom(n), symbole(s) {}

string Joueur::getNom() const {
    return nom;
}

string Joueur::setNom(string nom) const {
    return nom;
}

string Joueur::getSymbole() const{
    return symbole;
}

string Joueur::setSymbole(string s) const {

}