#include "Joueur.h"

Joueur::Joueur(string n, string s) : nom(n), symbole(s) {}

string Joueur::getNom() const {
    return nom;
}

void Joueur::setNom(string n) const {
    nom == n;
}

string Joueur::getSymbole() const{
    return symbole;
}

void Joueur::setSymbole(string s) const {
    symbole == s;
}