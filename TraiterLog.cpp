/*************************************************************************
                           TraiterLog  -  Classe contenant toutes les fonctions et methodes de traitement des logs
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <TraiterLog> (fichier TraiterLog.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <stdio.h>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "FluxLog.h"
#include "TraiterLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

void Analog()
{
    FluxLog src ("test.txt", ios_base::in);
    src.LireLigne().Afficher();
}

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
