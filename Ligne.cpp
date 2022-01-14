/*************************************************************************
                           Ligne  -  implemente une ligne de fichier log
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <Ligne> (fichier Ligne.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Ligne.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
Ligne::Ligne (string myip, string mylogName, string myuserName, string mydate, string mycible, int myhttpCode, int mysize, string myreferer, string myclient) : 
ip(myip), logName(mylogName), userName(myuserName), date(mydate), cible(mycible), httpCode(myhttpCode), size(mysize), referer(myreferer), client(myclient)
{
#ifdef MAP
    cout << "Appel au constructeur de <Ligne>" << endl;
#endif

} //----- Fin de Ligne


Ligne::~Ligne ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Ligne>" << endl;
#endif
} //----- Fin de ~Ligne


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
