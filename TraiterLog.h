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
#include <list>
using namespace std;
#include "FluxLog.h"
//------------------------------------------------------------- Constantes
typedef unordered_map<string,int> umSI; // map simple
typedef unordered_map<string,int>::iterator umit; // iterateur de map simple

typedef unordered_map<string , unordered_map<string,int>> umSumSI; // map double
typedef unordered_map<string , unordered_map<string,int>>::iterator umumit ; // iterateur de map double
//------------------------------------------------------------------ Types
struct Arguments { // structure contenant tous les arguments que l'on exploite
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
    // Mode d'emploi :
    // Traite les arguments de la ligne de commande et rempli la struct arguments avec les valeurs adequate

void Analog(Arguments mesArgs);
    // Mode d'emploi :
    // Analyse le fichier de log

void Top10( umSI & um);
    // Mode d'emploi :
    // Construit et affiche le top 10 des cibles les plus consulte

bool checkTimes( int hLigne , int hCond);
    // Mode d'emploi :
    // Verifie que l'heure de la requete correspond a celle souhaite

bool checkExtension( string cible );
    // Mode d'emploi :
    // Verifie que l'extension de fichier est souhaite par l'utilisateur

void Graph( umSumSI cptRefCib );
    // Mode d'emploi :
    // Construit le graph

void FillUM( FluxLog & src , Arguments & mesArgs , umSI & cptCible , umSumSI & cptRefCib);
    // Mode d'emploi :
    // Rempli les maps avec toutes les lignes du fichier log souhaite

#endif // TRAITERLOG_H