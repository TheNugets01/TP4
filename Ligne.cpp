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

//----------------------------------------------------- Méthodes publiques

    void Ligne::Afficher()
    {
        cout << "IP : " << ip << endl;
        cout << "logName : " << logName << endl;
        cout << "userName : " << userName << endl;
        cout << "date : " << date << endl;
        cout << "cible : " << cible << endl;
        cout << "httpCode : " << httpCode << endl;
        cout << "size : " << size << endl;
        cout << "referer : " << referer << endl;
        cout << "client : " << client << endl;
    }

//-------------------------------------------- Constructeurs - destructeur
Ligne::Ligne(const Ligne & uneLigne) :
ip(uneLigne.ip), logName(uneLigne.logName), userName(uneLigne.userName), date(uneLigne.date), cible(uneLigne.cible), httpCode(uneLigne.httpCode), size(uneLigne.size), referer(uneLigne.referer), client(uneLigne.client)
{
#ifdef MAP
    cout << "Appel au constructeur de copie <Ligne>" << endl;
#endif
}

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
