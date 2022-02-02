/*************************************************************************
                           TraiterLog  -  Classe contenant toutes les fonctions et methodes de traitement des logs
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe TraiterLog (fichier TraiterLog.h) ----------------
#if ! defined ( TRAITERLOG_H )
#define TRAITERLOG_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include <unordered_map>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct Arguments {
    bool g = false;
    bool e = false;
    bool t = false;
    string nomDot = "";
    string nomLog = "";
    int heure = 0;
};
//------------------------------------------------------------------------
// Rôle de la classe <TraiterLog>
// La classe TraiterLog contient toutes les fonctions et methodes de traitement des logs
//
//------------------------------------------------------------------------

Arguments TraiterArgs(int nbArg, char *listArg []);
void Analog(Arguments mesArgs);
void AfficherUM(unordered_map<string,int> & um);

#endif // TRAITERLOG_H