/*************************************************************************
                           Ligne  -  implemente une ligne de fichier log
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe Ligne (fichier Ligne.h) ----------------
#if ! defined ( LIGNE_H )
#define LIGNE_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
using namespace std;

#include <unordered_map>

struct Arguments;
class FluxLog;

//------------------------------------------------------------- Constantes
typedef unordered_map<string,int> umSI; // map simple
typedef unordered_map<string , unordered_map<string,int>> umSumSI;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Ligne>
// La classe ligne contient tous les attributs d'une ligne du fichier log
//
//------------------------------------------------------------------------

class Ligne
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//--------------------------------------------------------------- Getteurs

    friend void FillUM( FluxLog & src , Arguments & mesArgs , umSI & cptCible ,umSumSI & cptRefCib);

//-------------------------------------------- Constructeurs - destructeur

    Ligne (const Ligne & autre);
    // Mode d'emploi :
    // Construit la ligne a partir d'une autre ligne

    Ligne (string myip, string mylogName, string myuserName, string mydate, string mycible, int myhttpCode, int mysize, string myreferer, string myclient);
    // Mode d'emploi :
    // Construit la ligne a partir des infos extraites du fichier log

    virtual ~Ligne ( );
    // Mode d'emploi :
    // Detruit la ligne


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string ip;
    string logName;
    string userName;
    string date;
    string cible;
    int httpCode;
    int size;
    string referer;
    string client;

};

//-------------------------------- Autres définitions dépendantes de <Ligne>

#endif // LIGNE_H

