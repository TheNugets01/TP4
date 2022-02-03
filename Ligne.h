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
#include "TraiterLog.h"
//------------------------------------------------------------- Constantes

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

    //friend void Analog( Arguments mesArgs );

    void Afficher();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Ligne (const Ligne & autre);

    Ligne (string myip, string mylogName, string myuserName, string mydate, string mycible, int myhttpCode, int mysize, string myreferer, string myclient);
    // Mode d'emploi :
    // Construit la ligne a partir des infos extraites du fichier log

    virtual ~Ligne ( );
    // Mode d'emploi :
    // Detruit la ligne

    string date;
    string cible;
    int httpCode;
    string referer;
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string ip;
    string logName;
    string userName;
    int size;
    string client;

};

//-------------------------------- Autres définitions dépendantes de <Ligne>

#endif // LIGNE_H

