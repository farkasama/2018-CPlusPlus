#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <iostream>
#include <string>
#include "Plateau.hpp"

using namespace std;

class Affichage {
    public:
        Affichage();
        void afficherDame(Plateau* p, int t);
        void afficherEchec(Plateau* p, int t);
        void afficherPlateau(Plateau *p, int t);
        void afficherMoveObligatoire(vector<Position**>* v, int taille);
        void afficherMoveBot(vector<Position*> *v, int t);
        void afficherAideCommande();
        void afficherMenu();
};

#endif