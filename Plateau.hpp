#ifndef PLATEAU_H
#define PLATEAU_H

#include "Case.hpp"
#include <string>
#include <vector>

using namespace std;

class Plateau {
    protected:
        Case ***plateau;
        int taille;
        vector<Pion*> pionNoir;
        vector<Position*> movePionNoir;
    
    public:
        Plateau(int taille);
        virtual ~Plateau();

        //Fonctions simples
        virtual string toString(int x, int y);
        bool ifPion(int x, int y);
        void putPion(Pion* p);
        virtual bool ifBlancAGagne();
        virtual bool ifNoirAGagne();
        virtual int typeDePartie();

        //Getteurs
        vector<Position*>* getMovePionNoir();

        //Fonctions Annexes
        void supprimerPionNoir(Pion* p);

        virtual void moveTo(int d_x, int d_y, int a_x, int a_y);
        virtual bool canMoveTo(int d_x, int d_y, int a_x, int a_y, bool c);
        
        virtual bool moveObligatoire(bool c);
        virtual bool estUnMoveObligatoire(Position* d, Position* a);
        virtual bool aEncoreUnMoveObligatoire(Position* p);
        virtual vector<Position**>* getMoveObligatoire();

        virtual void jouerBot();
};

#endif

#ifndef PLATEAU_DAME_H
#define PLATEAU_DAME_H

class PlateauDame : public Plateau {
    private:
        vector<Position**> obligation;
        
    public:
        PlateauDame(int taille, bool vide);
        PlateauDame(int taille);
        ~PlateauDame();

        //Actions de base
        void moveTo(int d_x, int d_y, int a_x, int a_y);
        void putPion(int x, int y, bool c, bool dame);
        bool canMoveTo(int depart_x, int depart_y, int arrive_x, int arrive_y, bool c);
        bool canMoveToDame(int depart_x, int depart_y, int arrive_x, int arrive_y, bool c);
        int typeDePartie();

        //Getteurs
        vector<Position**>* getMoveObligatoire();
        
        //Rafle
        bool moveObligatoire(bool c);
        bool estUnMoveObligatoire(Position* d, Position* a);
        bool aEncoreUnMoveObligatoire(Position* p);
        void pushInVector(int d_x, int d_y, int a_x, int a_y);

        //Rafle avec un pion
        bool verification(int x, int y, int* nb, bool c);
        bool verification(int d_x, int d_y, int a_x, int a_y, bool c);
        void push(int x, int y, int i, int j, int* nb, int d, bool c);
        int maxMoveObligatoire(int x, int y, int d, bool c);

        // Rafle avec une dame
        bool verificationDame(int x, int y, int* nb, bool c);
        bool verificationDame(int x, int y, int i_x, int i_y, bool c);
        void pushDame(int x, int y, int i, int j, int* nb, int d, bool c);
        int maxMoveObligatoireDame(int i, int j, int d, bool c);
        int moveObligatoireDame(int x, int y, int i, int j, int d, bool c);

        //Bot
        void jouerBot();
};

#endif


#ifndef PLATEAU_ECHEC_H
#define PLATEAU_ECHEC_H

class PlateauEchec : public Plateau {
    private:

    public:
        PlateauEchec(int taille);
        PlateauEchec(int taille, bool c);
        ~PlateauEchec();

        string toString(int x, int y);
        int typeDePartie();

        bool canMoveTo(int d_x, int d_y, int a_x, int a_y, bool c);
        bool pasDePionSurLeChemin(int d_x, int d_y, int a_x, int a_y);

        bool ifBlancAGagne();
        bool ifNoirAGagne();

        void jouerBot();
};

#endif


#ifndef PLATEAU_MAKRUK_H
#define PLATEAU_MAKRUK_H

class PlateauMakruk : public PlateauEchec {
    private:

    public:
        PlateauMakruk(int taille);
        PlateauMakruk(int taille, bool v);
        ~PlateauMakruk();

        int typeDePartie();

};

#endif