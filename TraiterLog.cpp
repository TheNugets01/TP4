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

typedef unordered_map<string,int>::iterator umit;

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

void Analog()
{
    unordered_map<string,int> cptCible;
    FluxLog src ("test.txt", ios_base::in);
    int i = 0;
    while(i<4)
    {
        umit it;
        Ligne ligneCourante(src.LireLigne());

        int httpCode = ligneCourante.httpCode;
        string cible = ligneCourante.cible; 
        if(httpCode == 200 || httpCode == 304)
        {
            it = cptCible.find(cible);
            if(it == cptCible.end())
            {
                cptCible.insert({cible,1});
            }
            else
            {
                it->second++;
            }
        }
        i++;
    }
    AfficherUM(cptCible);
}

void AfficherUM(unordered_map<string,int> & um)
{
    for(umit it = um.begin(); it != um.end() ; ++it)
    {
        cout << '<' << it->first << ',' << it->second << '>' << endl;
    }
}
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
