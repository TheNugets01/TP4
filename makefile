EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all : analog

MAP : EXTFLAGS += -DMAP
MAP : analog

analog : Ligne.o main.o
		g++ -o analog Ligne.o main.o $(EXTFLAGS)

Ligne.cpp : Ligne.cpp
		g++ -c -g $(EXTFLAGS) Ligne.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp