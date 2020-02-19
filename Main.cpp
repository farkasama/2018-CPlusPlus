#include "Affichage.hpp"
#include "Plateau.hpp"
#include "Move.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int tailleEchec = 8;
const int tailleDame = 10;
int taille;
Plateau* p;
Affichage a;

void deplacement(Move* m, bool a) {
    bool test = m->getMove();
    do {
        m->inverser(taille);
        if (!test) {
            cout << "Les valeurs entrees ne sont pas bonnes" << endl;
            test = m->getMove();
        }
        else if (!m->isPossible(taille)){
            cout << "Les valeurs depassent le plateau" << endl;
            m->getMove();
            test = false;
        }
        else if (a && !p->ifPion(m->getPos()->getX(), m->getPos()->getY())) {
            cout << "Pas de pion selectionne" << endl;
            m->getMove();
            test = false;
        }
        else
            test = true;
    } while (!test);
}


bool canMove(Move* d, Move *a, bool obli) {
    if (!p->canMoveTo(d->getPos()->getX(), d->getPos()->getY(), a->getPos()->getX(), a->getPos()->getY(), true)){
        if (obli && p->estUnMoveObligatoire(d->getPos(), a->getPos())) {
            return true;
        }
        else {
            cout << "Le deplacement n'est pas reglementaire. Veulliez recommencer." << endl;
            return false;
        }
    }
    else if (obli && !p->estUnMoveObligatoire(d->getPos(), a->getPos())) {
        cout << "Le deplacement n'est pas un deplacement obligatoire. Veuillez recommencer." << endl;
        return false;
    }
    else
        return true;
}

void sauvegardePartie(string nomFichier) {
    ofstream fichier(nomFichier, ios::out | ios::trunc);
    if (fichier) {
        fichier << p->typeDePartie() << endl;
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j <taille; j++) {
                string str = p->toString(i, j);
                if (str.compare("  ") == 0)
                    fichier << "XX" << flush;
                else if (str.compare(" ") == 0)
                    fichier << "X" << flush;
                else
                    fichier << str << flush;
                if (j != taille-1)
                    fichier << " " << flush;
            }
            fichier << endl;
        }
        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier !" << endl;
    }
}

void afficher(int i) {
    if (i ==1) {
        a.afficherDame(p, taille);
    }
    else
        a.afficherEchec(p, taille);
}

void lirePartie(string nomFichier) {
    cout << nomFichier << endl;
    ifstream fichier(nomFichier, ios::in);

    if (fichier) {
        int type;
        fichier >> type;
        cout << type <<endl;

        if (type == 1) {
            taille = tailleDame;
            p = new PlateauDame(taille, true);
            for (int i = 0; i < taille; i++) {
                for (int j = 0; j < taille; j++) {
                    char pion;
                    fichier >> pion;
                    if (pion == 'N')
                        p->putPion(new PionNoir(i, j));
                    if (pion == 'B' )
                        p->putPion(new PionBlanc(i, j));
                    if (pion == 'Q')
                        p->putPion(new PionDameNoire(i, j));
                    if (pion == 'D')
                        p->putPion(new PionDameBlanche(i, j));
                }
            }
        }
        if (type == 2 || type == 3) {
            taille = tailleEchec;
            if (type == 2)
                p = new PlateauEchec(taille);
            else
                p = new PlateauMakruk(taille, true);

            for (int i = 0; i < taille; i++) {
                for (int j = 0; j < taille; j++) {
                    string pion;
                    fichier >> pion;
                    bool c;
                    if (pion[1] == 'B')
                        c = true;
                    else
                        c = false;
                    if (pion[0] == 'P' && c)
                        p->putPion(new PionEchecBlanc(i, j));
                    if (pion[0] == 'P' && !c)
                        p->putPion(new PionEchecNoir(i, j));
                    if (pion[0] == 'T')
                        p->putPion(new PionTour(i, j, c));
                    if (pion[0] == 'C')
                        p->putPion(new PionCavalier(i, j, c));
                    if (pion[0] == 'F')
                        p->putPion(new PionFou(i, j, c));
                    if (pion[0] == 'Q')
                        p->putPion(new PionReine(i, j, c));
                    if (pion[0] == 'K')
                        p->putPion(new PionRoi(i, j, c));
                    if (pion[0] == 'G')
                        p->putPion(new PionGraine(i, j, c));
                    if (pion[0] == 'N')
                        p->putPion(new PionNoble(i, j, c));
                }
            }
        }
        if (type == 4) {
            int partie;
            fichier >> partie;
            if (partie == 1) {
                taille = tailleDame;
                p = new PlateauDame(taille);
            }
            else {
                taille = tailleEchec;
                if (partie == 2) {
                    p = new PlateauEchec(taille, true);
                }
                else if (partie == 3) {
                    p = new PlateauMakruk(taille);
                }
            }
            while(!fichier.eof()) {
                afficher(partie);
                cout << "Appuiez sur 'Entrer' pour continuer" << endl;
                int a, b, c, d;
                fichier >> a >> b >> c >> d;
                cout << "Prochain deplacement :" << endl;
                cout << (taille-a) << (char)(b+'A') << "->" << (taille-c) << (char)(d+'A') << endl;
                getchar();
            }
            afficher(partie);
            cout << "La partie est termine !" << endl;
        }
        fichier.close();
    }
    else {
        cout << "Impossible de lire le fichier !" << endl;
    }
}


void startGame() {
    a.afficherPlateau(p,taille);
    Move depart;
    Move arrive;
    bool tour = true;
    int tourEtat = 1;
    int tourEtatMax = 1;
    string name = "tour" + to_string(tourEtat);
    sauvegardePartie(name);
    while (tour) {
        if (p->getMovePionNoir()->size() > 0)
            a.afficherMoveBot(p->getMovePionNoir(), taille);
        cout << "Que voulez faire ? (Ecrivez 'help' pour avoir les commandes)" << endl;
        int m = depart.getFristAction();
        while(m == 0) {
            m = depart.getFristAction();
            if (m == 0)
                cout << "Pas encore implementer ?" << endl;
        }
        if (m == 2) {
            break;
        }
        if (m == 3) {
            cout << "Choisissez le nom du fichier dans lequel la partie sera sauvegarde :" << endl;
            string nomFichier;
            getline(cin, nomFichier);
            sauvegardePartie(nomFichier);
            cout << "La partie a bien ete sauvegarde dans le fichier " << nomFichier << " !" << endl << endl;
        }
        if (m == 4)
            a.afficherAideCommande();
        if (m == 5) {
            if (tourEtat == 1) {
                cout << "Vous etes au premier tour, il est impossible de revenir en arriere." << endl;
            }
            else {
                tourEtat--;
                string name = "tour" + to_string(tourEtat);
                lirePartie(name);
                a.afficherPlateau(p, taille);
            }
        }
        if (m == 1) {
            bool can = false;
            do {
                bool obli = p->moveObligatoire(true);
                if (obli)
                    a.afficherMoveObligatoire(p->getMoveObligatoire(), taille);
                cout << "Quel pion voulez-vous deplacer ?" << endl;
                deplacement(&depart, true);

                cout << "Ou voulez vous le deplacer ?" << endl;
                deplacement(&arrive, false);

                if(depart.getPos()->equals(arrive.getPos()))
                    cout << "Les valeurs entrees sont les memes. Veuillez recommencer." << endl;
                else {
                    can = canMove(&depart, &arrive, obli);
                    if (can) {
                        p->moveTo(depart.getPos()->getX(), depart.getPos()->getY(), arrive.getPos()->getX(), arrive.getPos()->getY());
                    }
                    if (obli && p->moveObligatoire(true) && (p->aEncoreUnMoveObligatoire(arrive.getPos()))){
                        can = false;
                        a.afficherPlateau(p, taille);
                    }
                }

            } while(!can);


            if (p->ifBlancAGagne()) {
                a.afficherPlateau(p, taille);
                cout << "Vous avez gagne !" << endl;
                break;
            }
            p->jouerBot();
            a.afficherPlateau(p, taille);
            if (p->ifNoirAGagne()) {
                cout << "Vous avez perdu !" << endl;
            }
            tourEtat++;
            tourEtatMax = max(tourEtatMax, tourEtat);
            string name = "tour" + to_string(tourEtat);
            sauvegardePartie(name);
        }
    }
    cout << "La partie est termine" << endl;
    for (int i = 1; i <= tourEtatMax; i++) {
        string name = "tour" + to_string(i);
        remove(name.c_str());
    }
}


int main(int argc, char const *argv[])
{
    if (argc == 1) {
        char c = '1';
        do {
            a.afficherMenu();
            if (c < '1' || c > '4')
                cout << "La valeur entree n'est pas bonne. Veuillez recommencer." << endl;
            c = getchar();
        } while (c < '1' || c > '4');
        if (c == '1') {
            taille = tailleDame;
            p = new PlateauDame(taille);
            startGame();
        }
        if (c == '2') {
            taille = tailleEchec;
            p = new PlateauEchec(taille, true);
            startGame();
        }
        if (c == '3') {
            taille = tailleEchec;
            p = new PlateauMakruk(taille);
            startGame();
        }
        else {
            cout << "Vous avez quitter le jeu. A la prochaine !" << endl;
        }
        if (c >= '1' && c <= '3') {
            //delete p;
        }
    }
    else if (argc == 2) {
        lirePartie(argv[1]);
        startGame();
        delete p;
    }
    else {
        cout << "Trop de fichier passer en argument !" << endl;
    }
    return 0;
}