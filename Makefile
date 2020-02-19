CPP = g++ --std=c++11 -Wall

all : Main

Main : Affichage.o Main.o Plateau.o Move.o
	$(CPP) -o main *.o
	rm *.o

Move.o : Move.hpp
	$(CPP) -c Move.cpp -o Move.o

Affichage.o : Plateau.o
	$(CPP) -c Affichage.cpp -o Affichage.o

Main.o : Main.cpp Affichage.o Plateau.o
	$(CPP) -c Main.cpp -o Main.o

Plateau.o : Case.o
	$(CPP) -c Plateau.cpp -o Plateau.o

Case.o : Pion.o
	$(CPP) -c Case.cpp -o Case.o

Position.o : Position.hpp
	$(CPP) -c Position.cpp -o Position.o

Pion.o : Pion.hpp Position.o
	$(CPP) -c Pion.cpp -o Pion.o



clean :
	rm *.o