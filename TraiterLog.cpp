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
#include <string>
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//------------------------------------------------------ Include personnel

#include "FluxLog.h"
#include "TraiterLog.h"

//------------------------------------------------------------- Constantes

typedef unordered_map<string,int>::iterator umit;
typedef pair<string, int> site;

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

Arguments TraiterArgs(int nbArg, char *listArg[])
{
    Arguments mesArgs; //= {false,false,false,"","",-1};

    if( nbArg == 1 )
    // Traitement de l'oublie du nom du fichier log à traiter
    {
        cerr << "l'appel  à la fonction n'est pas bien formé" << endl;
        return mesArgs;
    }

    for(int i = 1 ; i < nbArg - 1 ; ++i) // traitement des modes si il y en a
    {
        //cout << listArg[i] << endl;

        if( listArg[i][0] == '-' )
        {
            if( listArg[i][1] == 'g' && i+2 <= nbArg ) // traitement du mode g
            {
                mesArgs.g = true;
                mesArgs.nomDot = listArg[++i];

                cout << "g/dot: 1/" << mesArgs.nomDot << endl;
            }
            else if ( listArg[i][1] == 'e' && i+1 <= nbArg ) // traitement du mode e
            {
                mesArgs.e = true;

                cout << "e : 1" << endl;
            }
            else if ( listArg[i][1] == 't' && i+2 <= nbArg ) // traitement du mode t
            {
                mesArgs.t = true;
                mesArgs.heure = stoi(listArg[++i]);

                cout << "t/heure: 1/" << mesArgs.heure << endl;
            }
            else
            {
                cerr << "l'appel de fonction est incorecte" << endl;
            }
        }
    }

    mesArgs.nomLog = listArg[nbArg - 1];
    cout << "Fichier Log : " << mesArgs.nomLog << endl;

    return mesArgs;
}

bool cmp(const site & l, const site & r)
{
    if (l.second != r.second) {
        return l.second > r.second;
    }
    return l.first > r.first;
}

void Top10(unordered_map<string,int> & um)
{
    vector<site> top10;
    copy(um.begin(),um.end(),back_inserter<vector<site>>(top10));
    sort(top10.begin(), top10.end(),cmp);

    int size = top10.size();
    if(size > 10)
    {
        size = 10;
    }
    for(int i = 0 ; i < size ; ++i)
    {
        cout << top10[i].second << " : " << top10[i].first  << endl;
    }
}

void Analog(Arguments mesArgs)
{
    unordered_map<string,int> cptCible;
    FluxLog src ("test.txt", ios_base::in);
    //FluxLog src ("anonyme.log", ios_base::in);
    int i = 0;
    while(src.peek()!=EOF)
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
    //AfficherUM(cptCible);
    Top10(cptCible);
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
