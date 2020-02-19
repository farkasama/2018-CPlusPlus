#ifndef CASE_H
#define CASE_H

#include "Pion.hpp"

class Case {
    private:
        Position pos;
        bool couleur;
        bool p;
        Pion *pion;
    public:
        Case(int x, int y, const bool c);
        ~Case();
        bool ifPion();
        bool caseEstNoir();
        bool caseEstBlanche();
        void setPion(Pion* p);
        Pion* getPion();
        Pion* getPionWithDelete();
        char toStringCouleur();
        char toStringPion();
        bool canMoveTo(int x, int y);
        Pion* supprimerPion();
};

#endif