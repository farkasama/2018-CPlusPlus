#ifndef PION_H
#define PION_H

#include "Position.hpp"
#include <iostream> 

class Pion {

    protected:
        Position *pos;
        bool couleur;
    
    public:
        Pion();
        Pion(int x, int y, bool c);
        virtual ~Pion();
        Position* getPos();
        void setPos(int x, int y);
        bool getCouleur();
        char toStringCouleur();
        virtual bool canMoveTo(int x, int y);
        virtual char toString();
        virtual bool estUneDame();
        virtual bool estUnPionEchec();
        virtual bool estUnCavalier();
        virtual bool estUnRoi();
};

#endif









/*
*       Jeu de Dame
*/

#ifndef PION_BLANC_H    
#define PION_BLANC_H

class PionBlanc : public Pion {
    public:
        PionBlanc(int x, int y);
        ~PionBlanc();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUneDame();
};

#endif


#ifndef PION_NOIR_H
#define PION_NOIR_H

class PionNoir : public Pion {
    public:
        PionNoir(int x, int y);
        ~PionNoir();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUneDame();
};

#endif


#ifndef PION_DAME_BLANCHE_H
#define PION_DAME_BLANCHE_H

class PionDameBlanche : public Pion {
    public:
        PionDameBlanche(int x, int y);
        ~PionDameBlanche();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUneDame();
};

#endif


#ifndef PION_DAME_NOIRE_H
#define PION_DAME_NOIRE_H

class PionDameNoire : public Pion {
    public:
        PionDameNoire(int x, int y);
        ~PionDameNoire();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUneDame();
};

#endif









/*
*       Jeu d'Echec
*/


#ifndef PION_ECHEC_NOIR_H
#define PION_ECHEC_NOIR_H

class PionEchecNoir : public Pion {
    private:
        bool premierMove;
    public:
        PionEchecNoir(int x, int y);
        ~PionEchecNoir();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUnPionEchec();
};

#endif


#ifndef PION_ECHEC_BLANC_H
#define PION_ECHEC_BLANC_H

class PionEchecBlanc : public Pion {
    private:
        bool premierMove;
    public:
        PionEchecBlanc(int x, int y);
        ~PionEchecBlanc();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUnPionEchec();
};

#endif


#ifndef PION_TOUR_H
#define PION_TOUR_H

class PionTour : public Pion {
    public:
        PionTour(int x, int y, bool c);
        ~PionTour();
        bool canMoveTo(int x, int y);
        char toString();
};

#endif

#ifndef PION_CAVALIER_H
#define PION_CAVALIER_H

class PionCavalier : public Pion {
    public:
        PionCavalier(int x, int y, bool c);
        ~PionCavalier();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUnCavalier();
};

#endif

#ifndef PION_FOU_H
#define PION_FOU_H

class PionFou : public Pion {
    public:
        PionFou(int x, int y, bool c);
        ~PionFou();
        bool canMoveTo(int x, int y);
        char toString();
};

#endif

#ifndef PION_REINE_H
#define PION_REINE_H

class PionReine : public Pion {
    public:
        PionReine(int x, int y, bool c);
        ~PionReine();
        bool canMoveTo(int x, int y);
        char toString();
};

#endif

#ifndef PION_ROI_H
#define PION_ROI_H

class PionRoi : public Pion {
    public:
        PionRoi(int x, int y, bool c);
        ~PionRoi();
        bool canMoveTo(int x, int y);
        char toString();
        bool estUnRoi();
};

#endif









/*
*       Jeu de Makruk
*/


#ifndef PION_GRAINE_H
#define PION_GRAINE_H

class PionGraine : public Pion {
    public:
        PionGraine(int x, int y, bool c);
        ~PionGraine();
        bool canMoveTo(int x, int y);
        char toString();
};

#endif


#ifndef PION_NOBLE_H
#define PION_NOBLE_H

class PionNoble : public Pion {
    public:
        PionNoble(int x, int y, bool c);
        ~PionNoble();
        bool canMoveTo(int x, int y);
        char toString();
};

#endif