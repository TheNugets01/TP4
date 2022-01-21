/*************************************************************************
                           LireLigne  -  Permet de lire une ligne du fichier log
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <LireLigne> (fichier LireLigne.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "LireLigne.h"

//------------------------------------------------------------- Constantes

#define TAILLEBUFFER 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Ligne LireLigne::Lecture()
{
    string ip;
    std::getline(*this,ip,' ');
    cout << ip << endl;
    Ligne ligneCourante(ip, "-", "-", "[08/Sep/2012:11:16:02 +0200]", "GET /temps/4IF16.html HTTP/1.1", 200, 12106, 
    "http://intranet-if.insa-lyon.fr/temps/4IF15.html", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1");
    return ligneCourante;
}

//-------------------------------------------- Constructeurs - destructeur
LireLigne::LireLigne (string nomFichier, ios_base::openmode mode)
{
    ifstream(nomFichier,mode);
#ifdef MAP
    cout << "Appel au constructeur de <LireLigne>" << endl;
#endif

} //----- Fin de Ligne


LireLigne::~LireLigne ( )
{

#ifdef MAP
    cout << "Appel au destructeur de <LireLigne>" << endl;
#endif
} //----- Fin de ~Ligne


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
