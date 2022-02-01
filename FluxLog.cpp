/*************************************************************************
                           FluxLog  -  Permet de specialiser le flux ifstream pour nous permettre de lire une ligne
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <FluxLog> (fichier FluxLog.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "FluxLog.h"

//------------------------------------------------------------- Constantes

#define TAILLEBUFFER 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Ligne FluxLog::LireLigne()
{
    string ip;
    string logName;
    string userName;
    string date;
    string cible;
    string sHttpCode;
    string sSize;
    string referer;
    string client;

    std::getline(*this,ip,' ');
    std::getline(*this,logName,' ');
    std::getline(*this,userName,' ');
    ignore(1);
    std::getline(*this,date,']');
    ignore(1);
    ignore(TAILLEBUFFER,' ');
    std::getline(*this,cible,' ');
    ignore(TAILLEBUFFER,'"');
    ignore(1);
    std::getline(*this,sHttpCode,' ');
    std::getline(*this,sSize,' ');
    ignore(1);
    std::getline(*this,referer,'"');
    ignore(2);
    std::getline(*this,client,'"');
    ignore(TAILLEBUFFER,'\n');
    int httpCode = stoi(sHttpCode);
    int size;
    if(sSize != "-")
    {
        size = stoi(sSize);
    }
    else
    {  
        size = 0;
    }
    Ligne ligneCourante(ip,logName,userName,date,cible,httpCode,size,referer,client);
    return ligneCourante;
}

//-------------------------------------------- Constructeurs - destructeur
FluxLog::FluxLog (string nomFichier, ios_base::openmode mode) : ifstream(nomFichier,mode)
{

#ifdef MAP
    cout << "Appel au constructeur de <FluxLog>" << endl;
#endif

} //----- Fin de Ligne


FluxLog::~FluxLog ( )
{

#ifdef MAP
    cout << "Appel au destructeur de <FluxLog>" << endl;
#endif
} //----- Fin de ~Ligne


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
