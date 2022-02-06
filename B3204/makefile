EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all : analog

MAP : EXTFLAGS += -DMAP
MAP : analog

analog : Ligne.o FluxLog.o TraiterLog.o main.o
		g++ -o analog FluxLog.o Ligne.o TraiterLog.o main.o $(EXTFLAGS)

Ligne.cpp : Ligne.cpp
		g++ -c -g $(EXTFLAGS) Ligne.cpp

FluxLog.cpp : FluxLog.cpp
		g++ -c -g $(EXTFLAGS) FluxLog.cpp

TraiterLog.cpp : TraiterLog.cpp
		g++ -c -g $(EXTFLAGS) TraiterLog.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp