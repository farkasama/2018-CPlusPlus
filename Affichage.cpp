#include "Affichage.hpp"

Affichage::Affichage() {}

void Affichage::afficherPlateau(Plateau *p, int t) {
    system("clear");
    if (t == 10)
        afficherDame(p, t);
    else
        afficherEchec(p, t);
}

void Affichage::afficherDame(Plateau* p, int t) {
    for (int i = -1; i < t; i++) {
        for (int j = -1; j < t; j++) {
            if (i == -1) {
                if (j == -1) {
                    cout << "X" << "  " << "| " << flush;
                }
                else {
                    cout << (char)('A'+j) <<" | " << flush;
                }
            }
            else {
                if (j == -1) {
                    if ((t-i)>9)
                        cout << (t-i) << " | " << flush;
                    else
                        cout << (t-i) << "  " << "| " << flush;
                }
                else {
                    cout << p->toString(i, j) << " | " << flush;
                }
            }
        }
        cout << endl;
        if (i == t-1) {
            for (int j = 0; j < t; j++) {
                cout << "----" << flush;
            }
            cout << "---|" << endl;
        }
        else {
            cout << "---+" << flush;
            for (int j = 0; j < t-1; j++) {
                cout << "---+" << flush;
            }
            cout << "---|" << endl;
        }
    }
}

void Affichage::afficherEchec(Plateau* p, int t) {
    for (int i = -1; i < t; i++) {
        for (int j = -1; j < t; j++) {
            if (i == -1) {
                if (j == -1)
                    cout << "X" << " | " << flush;
                else
                    cout << (char)('A'+j) << "  | " << flush;
            }
            else {
                if (j == -1) {
                    cout << (t-i) << " | " << flush;
                }
                else
                    cout << p->toString(i, j) << " | " << flush;
            }
        }
        cout << endl;
        if (i == t-1) {
            for (int j = 0; j < t; j++) {
                cout << "-----" << flush;
            }
            cout << "--|" << endl;
        }
        else {
            cout << "--+" << flush;
            for (int j = 0; j < t-1; j++)
                cout << "----+" << flush;
            cout << "----|" << endl;
        }
    }
}


void Affichage::afficherMoveObligatoire(vector<Position**>* p, int taille) {
    cout << "Vous avez un ou des deplacement(s) obligatoire(s) a faire."
        << endl << "Le(s) voici :" <<endl;
    for(unsigned int i = 0; i < p->size(); i++) {
        cout << (taille-(*p)[i][0]->getX()) << (char)((*p)[i][0]->getY()+'A') << flush;
        cout << "->" << flush;
        cout << (taille-(*p)[i][1]->getX()) << (char)((*p)[i][1]->getY()+'A') << endl;
    }
}

void Affichage::afficherMoveBot(vector<Position*>* v, int taille) {
    cout << "Le joueur automatique a fait les deplacements suivants :" << endl;
    for (unsigned int i = 0; i < v->size(); i++) {
        cout << (taille-(*v)[i]->getX()) << (char)((*v)[i]->getY()+'A') << flush;
        if (i < v->size()-1)
            cout << "->" << flush;
    }
    cout << endl;
}


void Affichage::afficherAideCommande() {
    cout << endl;
    cout << "Voici les commandes possibles :" << endl;
    cout << "move/deplacer : pour deplacer un pion." << endl;
    cout << "save/sauvegarder : sauvegarder l'etat de la partie en cours." << endl;
    cout << "abandonenr : abandonner la partie." << endl << endl;
}

void Affichage::afficherMenu() {
    system("clear");
    cout << "Choisissez le jeu (tapez le numero et appuyez sur entrer):" << endl;
    cout << "1 : Jeu de dame" << endl;
    cout << "2 : Jeu d'echec" << endl;
    cout << "3 : Jeu de makruk" << endl;
    cout << "4 : Quitter" << endl << endl;
}