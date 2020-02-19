#include "Plateau.hpp"

Plateau::Plateau(int taille) {
    this->taille = taille;
    this->plateau = new Case**[taille];
    for (int i = 0; i < taille; i++) {
        this->plateau[i] = new Case*[taille];
        for (int j = 0; j < taille; j++) {
            if (i%2 == 0) {
                if (j%2 == 0) {
                    this->plateau[i][j] = new Case(i, j, true);
                }
                else
                    this->plateau[i][j] = new Case(i, j, false);
            }
            else{
                if (j%2 == 0)
                    this->plateau[i][j] = new Case(i, j, false);
                else
                    this->plateau[i][j] = new Case(i, j, true);
            }
        }
    }
}

Plateau::~Plateau() {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            delete plateau[i][j];
        }
        delete[] plateau[i];
    }
    delete[] plateau;

    if (!movePionNoir.empty()) {
        for (unsigned int i = 0; i < movePionNoir.size(); i++) {
            delete movePionNoir[i];
        }
    }
}


/*
*      +-------------------+
*      | Fonctions simples |
*      +-------------------+
*/

string Plateau::toString(int x, int y) {
    string str;
    str += this->plateau[x][y]->toStringPion();
    return str;
}

bool Plateau::ifPion(int x, int y) {
    return plateau[x][y]->ifPion();
}

void Plateau::putPion(Pion* p) {
    if (!p->getCouleur())
        pionNoir.push_back(p);
    plateau[p->getPos()->getX()][p->getPos()->getY()]->setPion(p);
}

bool Plateau::ifBlancAGagne() {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (plateau[i][j]->ifPion() &&
                !plateau[i][j]->getPion()->getCouleur())
                return false;
        }
    }
    return true;
}

bool Plateau::ifNoirAGagne() {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (plateau[i][j]->ifPion() &&
                plateau[i][j]->getPion()->getCouleur())
                return false;
        }
    }
    return true;
}

int Plateau::typeDePartie() {
    return 0;
}


/*
*      +-----------+
*      | Guetteurs |
*      +-----------+
*/

vector<Position*>* Plateau::getMovePionNoir() {
    return &movePionNoir;
}


/*
*      +-------------------+
*      | Fonctions annexes |
*      +-------------------+
*/

void Plateau::supprimerPionNoir(Pion* p) {
    for (unsigned int i = 0; i < pionNoir.size(); i++) {
        if (pionNoir[i] == p) {
            //Pion* p = pionNoir[i];
            pionNoir.erase(pionNoir.begin()+i-1); // ???????
            //delete p;
        }
    }
}


void Plateau::moveTo(int depart_x, int depart_y, int arrive_x, int arrive_y) {
    Pion* p = plateau[depart_x][depart_y]->getPionWithDelete();
    p->setPos(arrive_x, arrive_y);
    plateau[arrive_x][arrive_y]->setPion(p);
}

bool Plateau::canMoveTo(int d_x, int d_y, int a_x, int a_y, bool c) {
    return true;
}

bool Plateau::moveObligatoire(bool c) {
    return false;
}

bool Plateau::estUnMoveObligatoire(Position* d, Position* a) {
    return false;
}

bool Plateau::aEncoreUnMoveObligatoire(Position* p) {
    return false;
}

vector<Position**>* Plateau::getMoveObligatoire() {
    return nullptr;
}

void Plateau::jouerBot() {}














/*
*
##################################################################
#                       CLASS JEU DE DAME                        #
##################################################################
*
*/

PlateauDame::PlateauDame(int taille, bool vide) : Plateau(taille) {}

PlateauDame::PlateauDame(int taille) : Plateau(taille) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < taille; j++) {
            if(plateau[i][j]->caseEstNoir()){
                PionNoir* p = new PionNoir(i,j);
                pionNoir.push_back(p);
                plateau[i][j]->setPion(p);
            }
        }
    }
    for (int i = taille-4; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if(plateau[i][j]->caseEstNoir()){
                plateau[i][j]->setPion(new PionBlanc(i, j));
            }
        }
    }
}

PlateauDame::~PlateauDame() {
    if (!obligation.empty()) {
        for (unsigned int i = 0; i < obligation.size(); i++) {
            delete obligation[i][0];
            delete obligation[i][1];
            delete[] obligation[i];
        }
    }
}


/*
*      +-----------------+
*      | Actions de base |
*      +-----------------+
*/

void PlateauDame::moveTo(int d_x, int d_y, int a_x, int a_y) {
    Plateau::moveTo(d_x, d_y, a_x, a_y);

    Pion* p =plateau[a_x][a_y]->getPion();

    if (a_x - d_x == 2) {
        if (a_y - d_y == 2) {
            supprimerPionNoir(plateau[d_x+1][d_y+1]->getPionWithDelete());
        }
        else {
            supprimerPionNoir(plateau[d_x+1][d_y-1]->getPionWithDelete());
        }
    }
    else if (a_x - d_x == -2) {
        if (a_y - d_y == 2)
            supprimerPionNoir(plateau[d_x-1][d_y+1]->getPionWithDelete());
        else
            supprimerPionNoir(plateau[d_x-1][d_y-1]->getPionWithDelete());
    }
    if (!p->estUneDame()) {
        if (a_x == 9 && !p->getCouleur()) {
            supprimerPionNoir(p);
            Pion* a = new PionDameNoire(a_x, a_y);
            pionNoir.push_back(a);
            plateau[a_x][a_y]->setPion(a);
        }
        else if (a_x == 0 && p->getCouleur()) {
            plateau[a_x][a_y]->setPion(new PionDameBlanche(a_x, a_y));
        }
    }
    else {
        int a = -1;
        int b = -1;
        if (a_x > d_x)
            a = 1;
        if (a_y > d_y)
            b = 1;
        for (int i = 0; i < abs(a_x-d_x); i++) {
            if (plateau[d_x+(i*a)][d_y+(i*b)]->ifPion())
                supprimerPionNoir(plateau[d_x+(i*a)][d_y+(i*b)]->getPionWithDelete());
        }
    }
}

void PlateauDame::putPion(int x, int y, bool c, bool dame) {
    if (c)
        if (dame)
            plateau[x][y]->setPion(new PionDameBlanche(x,y));
        else
            plateau[x][y]->setPion(new PionBlanc(x, y));
    else {
        if (dame) {
            Pion* p = new PionDameNoire(x,y);
            pionNoir.push_back(p);
            plateau[x][y]->setPion(p);
        }
        else {
            PionNoir* p = new PionNoir(x,y);
            pionNoir.push_back(p);
            plateau[x][y]->setPion(p);
        }
    }
}


bool PlateauDame::canMoveTo(int depart_x, int depart_y, int arrive_x, int arrive_y, bool c) {
    if (plateau[depart_x][depart_y]->ifPion()) {
        if (plateau[depart_x][depart_y]->getPion()->getCouleur() == c) {
            if (!plateau[arrive_x][arrive_y]->ifPion()) {
                if (!plateau[depart_x][depart_y]->getPion()->estUneDame())
                    return plateau[depart_x][depart_y]->canMoveTo(arrive_x, arrive_y);
                else
                    return plateau[depart_x][depart_y]->canMoveTo(arrive_x, arrive_y) &&
                    canMoveToDame(depart_x, depart_y,arrive_x, arrive_y, c);
            }
        }
    }
    return false;
}

bool PlateauDame::canMoveToDame(int depart_x, int depart_y, int arrive_x, int arrive_y, bool c) {
    int a = -1;
    int b = -1;
    if (arrive_x > depart_x)
        a = 1;
    if (arrive_y > depart_y)
        b = 1;
    bool test = true;
    for (int i = 1; i < abs(arrive_x - depart_x); i++) {
        if (plateau[depart_x+(i*a)][depart_y+(i*b)]->ifPion()) {
            if (plateau[depart_x+(i*a)][depart_y+(i*b)]->getPion()->getCouleur() == c)
                return false;
            else if (test)
                test = false;
            else
                return false;
        }
    }
    return true;
}


int PlateauDame::typeDePartie() {
    return 1;
}



/*
*      +-----------+
*      | Guetteurs |
*      +-----------+
*/

vector<Position**>* PlateauDame::getMoveObligatoire() {
    return &obligation;
}


/*
*      +-------+
*      | Rafle |
*      +-------+
*/

bool PlateauDame::moveObligatoire(bool c) {
    bool a = false;
    obligation.clear();
    int nb = 0;
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (verification(i, j, &nb, c)) {
                a = true;
            }
        }
    }
    return a;
}


bool PlateauDame::estUnMoveObligatoire(Position* d, Position* a) {
    for (unsigned int i = 0; i < obligation.size(); i++) {
        if (obligation[i][0]->equals(d) && obligation[i][1]->equals(a))
            return true;
    }
    return false;
}

bool PlateauDame::aEncoreUnMoveObligatoire(Position* p) {
    if (obligation.empty())
        return false;
    for (unsigned int i = 0; i < obligation.size(); i++) {
        if (p->equals(obligation[i][0]))
            return true;
    }
    return false;
}

void PlateauDame::pushInVector(int d_x, int d_y, int a_x, int a_y) {
    Position ** p = new Position*[2];
    p[0] = new Position(d_x,d_y);
    p[1] = new Position(a_x,a_y);
    if (!estUnMoveObligatoire(p[0], p[1]))
        obligation.push_back(p);
}


/*
*      +--------------------+
*      | Rafle avec un pion |
*      +--------------------+
*/

bool PlateauDame::verification(int x, int y, int* nb, bool c) {
    if (!plateau[x][y]->ifPion() || !(plateau[x][y]->getPion()->getCouleur() == c))
        return false;
    else if (plateau[x][y]->getPion()->estUneDame()) {
        return verificationDame(x, y, nb, c);
    }
    bool a = false;
    if (verification(x, y, -2, -2, c)) {
        push(x, y, x-2, y-2, nb, 0, c);
        a = true;
    }
    if (verification(x, y, -2, 2, c)) {
        push(x, y, x-2, y+2, nb, 1, c);
        a = true;
    }
    if (verification(x, y, 2, -2, c)) {
        push(x, y, x+2, y-2, nb, 2, c);
        a = true;
    }
    if (verification(x, y, 2, 2, c))  {
        push(x, y, x+2, y+2, nb, 3, c);
        a = true;
    }
    return a;
}


bool PlateauDame::verification(int x, int y, int inc_x, int inc_y, bool c) {
    int dep_x;
    int dep_y;
    if (inc_x == -2)
        dep_x = -1;
    else
        dep_x = 1;
    if (inc_y == -2)
        dep_y = -1;
    else
        dep_y = 1;
    return x+inc_x >= 0 && x+inc_x < taille 
        && y+inc_y >= 0 && y+inc_y < taille
        && plateau[x+dep_x][y+dep_y]->ifPion()
        && !(plateau[x+dep_x][y+dep_y]->getPion()->getCouleur() == c)
        && !plateau[x+inc_x][y+inc_y]->ifPion();
}

void PlateauDame::push(int x, int y, int i, int j, int* nb, int d, bool c) {
    int max = 1+maxMoveObligatoire(i, j, d, c);
    if (max > *nb){
        obligation.clear();
        *nb = max;
        pushInVector(x, y, i, j);
    }
    else if (max == *nb)
        pushInVector(x, y, i, j);
}

int PlateauDame::maxMoveObligatoire(int x, int y, int d, bool c) {
    int i = 0;
    if (verification(x,y, -2, -2, c) && d != 3)
        i = 1 + maxMoveObligatoire(x-2, y-2, 0, c);
    if (verification(x,y, -2, 2, c) && d != 2)
        i = max(i, 1+maxMoveObligatoire(x-2, y+2, 1, c));
    if (verification(x, y, 2, -2, c) && d != 1)
        i = max(i, 1+maxMoveObligatoire(x+2, y-2, 2, c));
    if (verification(x, y, 2, 2, c) && d != 0)
        i = max(i, 1+maxMoveObligatoire(x+2, y+2, 3, c));
    return i;
}


/*
*      +---------------------+
*      | Rafle avec une dame |
*      +---------------------+
*/

bool PlateauDame::verificationDame(int x, int y, int* nb, bool c) {
    bool a = false;
    if (verificationDame(x, y, -1, -1, c)) {
        pushDame(x, y, -1, -1, nb, 0, c);
        a = true;
    }
    if (verificationDame(x, y, -1, 1, c)) {
        pushDame(x, y, -1, 1, nb, 1, c);
        a = true;
    }
    if (verificationDame(x, y, 1, -1, c)) {
        pushDame(x, y, 1, -1, nb, 2, c);
        a = true;
    }
    if (verificationDame(x, y, 1, 1, c)) {
        pushDame(x, y, -1, 1, nb, 3, c);
        a = true;
    }
    return a;
}

bool PlateauDame::verificationDame(int x, int y, int i_x, int i_y, bool c) {
    int a = x;
    int b = y;
    if (i_x == 1) {
        a = taille-x-1;
    }
    if (i_y == 1) {
        b = taille-y-1;
    }
    for (int i = 1; i < min(a, b); i++) {
        if (plateau[x+(i*i_x)][y+(i*i_y)]->ifPion()) {
            if (plateau[x+(i*i_x)][y+(i*i_y)]->getPion()->getCouleur() == c) {
                return false;
            }
            if (!plateau[x+(i*i_x + i_x)][y+(i*i_y) + i_y]->ifPion()) {
                return true;
            }
        }
    }
    return false;
}

void PlateauDame::pushDame(int x, int y, int i, int j, int* nb, int d, bool c) {
    int a = x+1;
    int b = y+1;
    if (i == 1)
        a = taille-x;
    if (j == 1)
        b = taille-y;
    bool test = true;
    for (int k = 1; k < min(a, b); k++) {
        if (test && plateau[x+(k*i)][y+(k*j)]->ifPion()) {
            test = false;
        }
        else if (!test && plateau[x+(k*i)][y+(k*j)]->ifPion()) {
            break;
        }
        else if (!test) {
            int max = 1+maxMoveObligatoireDame(x+(k*i), y+(k*j), d, c);
            if (max > *nb) {
                obligation.clear();
                *nb = max;
                pushInVector(x, y, x+(k*i), y+(k*j));
            }
            else if (max == *nb) {
                pushInVector(x, y, x+(k*i), y+(k*j));
            }
        }
    }
}

int PlateauDame::moveObligatoireDame(int x, int y, int i, int j, int d, bool c) {
    int nombre = 0;
    int a = x;
    int b = y;
    if (i == 1)
        a = taille-x-1;
    if (j == 1)
        b = taille-x-1;
    bool test = true;
    for (int k = 1; k < min(a, b); k++) {
        if (test && plateau[x+(k*i)][y+(k*j)]->ifPion()) {
            test = false;
        }
        else if (!test && plateau[x+(k*i)][y+(k*j)]->ifPion()) {
            return nombre;
        }
        else if (!test) {
            nombre = max(nombre, maxMoveObligatoireDame(x+(k*i), y+(k*j), d , c));
        }
    }
    return nombre;
}

int PlateauDame::maxMoveObligatoireDame(int x, int y, int d, bool c) {
    int i = 0;
    if (d != 3 && verificationDame(x, y, -1, -1, c)) {
        moveObligatoireDame(x, y, -1, -1, d , c);
    }

    if (d != 2 && verificationDame(x, y, -1, 1, c)) {
        moveObligatoireDame(x, y, -1, 1, d , c);
    }
    if (d != 1 && verificationDame(x, y, 1, -1, c)) {
        moveObligatoireDame(x, y, 1, -1, d , c);
    }
    if (d != 0 && verificationDame(x, y, 1, 1, c)) {
        moveObligatoireDame(x, y, 1, 1, d , c);
    }
    return i;
}


/*
*      +-----+
*      | Bot |
*      +-----+
*/

void PlateauDame::jouerBot() {
    movePionNoir.clear();
    srand(time(NULL));
    if (moveObligatoire(false)) {
        int nb;
        int r;
        bool dernier = true;
        Position* p;
        do {
            nb = 0;
            r = rand() % obligation.size();
            if (dernier || 
            (!dernier && p->equals(new Position(obligation[r][0]->getX(), obligation[r][0]->getY())))) {
                moveTo(obligation[r][0]->getX(), obligation[r][0]->getY(), 
                    obligation[r][1]->getX(), obligation[r][1]->getY());
                    p = obligation[r][1];
                if (dernier) {
                    movePionNoir.push_back(obligation[r][0]);
                    movePionNoir.push_back(obligation[r][1]);
                    dernier = false;
                }
                else
                    movePionNoir.push_back(obligation[r][1]);
            }
        } while(verification(obligation[r][1]->getX(), obligation[r][1]->getY(), &nb, false));
    }
    else {
        Position* d;
        Position* a;
        bool can = false;
        do {
            int r = rand() % pionNoir.size();
            int s = rand() % 2;
            d = pionNoir[r]->getPos();
            if (!pionNoir[r]->estUneDame()) {
                if (s == 0) {
                    a = new Position(d->getX()+1, d->getY()-1);
                }
                else {
                    a = new Position(d->getX()+1, d->getY()+1);
                }
                if (!(a->getX() < 0 || a->getX() >= taille || a->getY() < 0 || a->getY() >= taille) &&
                    canMoveTo(d->getX(), d->getY(), a->getX(), a->getY(), false)) {
                    can = true;
                }
            }
            else {
                int x = rand() % taille;
                int y = rand() % taille;
                a = new Position(x, y);
                can = canMoveTo(d->getX(), d->getY(), x, y, false);
            }
        } while (!can);
        movePionNoir.push_back(new Position(d->getX(), d->getY()));
        movePionNoir.push_back(a);
        moveTo(d->getX(), d->getY(), a->getX(), a->getY());
    }
}














/*
*
##################################################################
#                       CLASS JEU D'ECHEC                        #
##################################################################
*
*/

PlateauEchec::PlateauEchec(int taille) : Plateau(taille) {}


PlateauEchec::PlateauEchec(int taille, bool c) : Plateau(taille) {
	Pion* p;

	p = new PionTour(0, 0, false);
	pionNoir.push_back(p);
	plateau[0][0]->setPion(p);
	plateau[taille-1][0]->setPion(new PionTour(taille-1, 0, true));


	p = new PionTour(0, taille-1, false);
	pionNoir.push_back(p);
	plateau[0][taille-1]->setPion(p);
	plateau[taille-1][taille-1]->setPion(new PionTour(taille-1, taille-1, true));

	p = new PionCavalier(0, 1, false);
	pionNoir.push_back(p);
	plateau[0][1]->setPion(p);
	plateau[taille-1][1]->setPion(new PionCavalier(taille-1, 1, true));


	p = new PionCavalier(0, taille-2, false);
	pionNoir.push_back(p);
	plateau[0][taille-2]->setPion(p);
	plateau[taille-1][taille-2]->setPion(new PionCavalier(taille-1, taille-2, true));


	p = new PionFou(0, 2, false);
	pionNoir.push_back(p);
	plateau[0][2]->setPion(p);
	plateau[taille-1][2]->setPion(new PionFou(taille-1, 2, true));


	if(c) {
		
		for (int i = 0; i < taille; i++) {
			p = new PionEchecNoir(1, i);
			pionNoir.push_back(p);
			plateau[1][i]->setPion(p);
			plateau[taille-2][i]->setPion(new PionEchecBlanc(taille-2, i));
		}


		p = new PionFou(0, taille-3, false);
		pionNoir.push_back(p);
		plateau[0][taille-3]->setPion(p);
		plateau[taille-1][taille-3]->setPion(new PionFou(taille-1, taille-3, true));


		p = new PionReine(0, 3, false);
		pionNoir.push_back(p);
		plateau[0][3]->setPion(p);
		plateau[taille-1][3]->setPion(new PionReine(taille-1, 3, true));
	
        p = new PionRoi(0, 4, false);
	    pionNoir.push_back(p);
	    plateau[0][4]->setPion(p);
	    plateau[taille-1][4]->setPion(new PionRoi(taille-1, 4, true));
    }
}

PlateauEchec::~PlateauEchec() {}


string PlateauEchec::toString(int x, int y) {
	string str = Plateau::toString(x, y);
	if (plateau[x][y]->ifPion())
		str += plateau[x][y]->getPion()->toStringCouleur();
	else
		str += " ";
	return str;
}

int PlateauEchec::typeDePartie() {
    return 2;
}



bool PlateauEchec::canMoveTo(int d_x, int d_y, int a_x, int a_y, bool c) {
	if (!plateau[d_x][d_y]->getPion()->canMoveTo(a_x, a_y) ||
		(plateau[a_x][a_y]->ifPion() && plateau[a_x][a_y]->getPion()->getCouleur() == c))
		return false;
	if (plateau[d_x][d_y]->getPion()->estUnCavalier())
		return true;
	if (plateau[d_x][d_y]->getPion()->estUnPionEchec() &&
		abs(a_y-d_y) == 1 && plateau[a_x][a_y]->ifPion() &&
		(plateau[a_x][a_y]->getPion()->getCouleur() != c))
		return true;
	if (plateau[d_x][d_y]->getPion()->estUnPionEchec() &&
		abs(a_y-d_y) == 1)
		return false;
    return pasDePionSurLeChemin(d_x, d_y, a_x, a_y);
}

bool PlateauEchec::pasDePionSurLeChemin(int d_x, int d_y, int a_x, int a_y) {
    if (abs(a_x-d_x)> 1 || abs(a_y-d_y) > 1) {
		int a = a_x-d_x;
		int b = a_y-d_y;
		int inc_x = 1;
		int inc_y = 1;
		if (a < 0)
		    inc_x = -1;
		if (b < 0)
		    inc_y = -1;
		if (a == 0) {
			for (int i = 1; i < abs(b); i++) {
				if (plateau[d_x][d_y+(i*inc_y)]->ifPion())
					return false;
			}
		}
		else if (b == 0) {
			for (int i = 1; i < abs(a); i++) {
				if (plateau[d_x+(i*inc_x)][d_y]->ifPion())
					return false;
			}
		}
		else {
			if (a < 0)
				a = -1;
			else
				a = 1;
			if (b < 0)
				b = -1;
			else
				b = 1;
			for (int i = 1; i < abs(a_x-d_x); i++) {
				if (plateau[d_x+(i*a)][d_y+(i*b)]->ifPion()) {
					return false;
				}
			}
		}
	}
    return true;
}

bool PlateauEchec::ifBlancAGagne() {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (plateau[i][j]->ifPion() && plateau[i][j]->getPion()->estUnRoi() &&
                !plateau[i][j]->getPion()->getCouleur())
                    return false;
        }
    }
    return true;
}

bool PlateauEchec::ifNoirAGagne() {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (plateau[i][j]->ifPion() && plateau[i][j]->getPion()->estUnRoi() &&
                plateau[i][j]->getPion()->getCouleur())
                    return false;
        }
    }
    return true;
}

void PlateauEchec::jouerBot() {
    srand(time(NULL));
    int r;
    int x;
    int y;
    do {
        r = rand() % pionNoir.size();
        x = rand()%taille;
        y = rand()%taille;
    } while (!(canMoveTo(pionNoir[r]->getPos()->getX(),
        pionNoir[r]->getPos()->getY(), x, y, false)));
    moveTo(pionNoir[r]->getPos()->getX(),
        pionNoir[r]->getPos()->getY(), x, y);
}














/*
*
##################################################################
#                       CLASS JEU DE MAKRUK                      #
##################################################################
*
*/

PlateauMakruk::PlateauMakruk(int taille, bool v) : PlateauEchec(taille) {}


PlateauMakruk::PlateauMakruk(int taille) : PlateauEchec(taille, false) {
    Pion* p;
    for (int i = 0; i < taille; i++) {
        p = new PionEchecNoir(2, i);
        pionNoir.push_back(p);
        plateau[2][i]->setPion(p);

        plateau[taille-3][i]->setPion(new PionEchecBlanc(taille-3, i));
    }

    p = new PionNoble(0, taille-3, false);
	pionNoir.push_back(p);
	plateau[0][taille-3]->setPion(p);
	plateau[taille-1][taille-3]->setPion(new PionNoble(taille-1, taille-3, true));
	
    p = new PionGraine(0, 3, false);
	pionNoir.push_back(p);
	plateau[0][3]->setPion(p);
	plateau[taille-1][3]->setPion(new PionGraine(taille-1, 4, true));
	
    p = new PionRoi(0, 4, false);
	pionNoir.push_back(p);
	plateau[0][4]->setPion(p);
	plateau[taille-1][4]->setPion(new PionRoi(taille-1, 3, true));
}

PlateauMakruk::~PlateauMakruk() {}


int PlateauMakruk::typeDePartie() {
    return 3;
}