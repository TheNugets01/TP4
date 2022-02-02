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

Arguments TraiterArgs(int nbArg, char *Arg[])
{
    Arguments mesArgs; //= {'\0',"","",-1};
    
    string listArg = "";
    for(int i=0 ; Arg[i] != NULL ; ++i)
    {
            listArg += Arg[i]; // = ./analog-gfichier.dot\0
    }

    listArg.erase(0 , 8); // enleve le ./analog des attributs

    if( listArg.empty() )
    {
        cerr << "Le fichier .log à analyser n'est pas défini" << endl;
    }
    else
    {
        int str_it = 0;
        //if ( listArg[0] == '-' ) //traitement des modes
        //{
        while( listArg[ str_it ] == '-' && str_it < 1000)
        {
            ++str_it;
            if( listArg[ str_it ] == 'g') // traitement du mode g
            {
                mesArgs.g = true;
                cout << "g : " << mesArgs.g << endl;

                string verifType = "";
                
                ++str_it;
                
                do
                {
                    verifType.clear();
                    for(int i = 0 ; i < 4 && str_it + i <=  listArg.length() ; ++i)
                    {
                        verifType += listArg[ str_it + i];
                    }

                    mesArgs.nomDot += listArg[ str_it ];

                    ++str_it;

                }while( verifType != ".dot");

                str_it+=3; // permet de se placer au niveau du prochain '-' si il existe
                
                cout << mesArgs.nomDot + "dot" << endl;
            }
            else if( listArg[ str_it ] == 'e') // traitement du mode e
            {
                mesArgs.e = true;
                cout << "e : " << mesArgs.e << endl;
                ++str_it;
            }
            else if( listArg[ str_it ] == 't')// traitement du mode t
            {
                mesArgs.t = true;
                cout << "t : " << mesArgs.t;
                mesArgs.heure = (int(listArg[ ++str_it ]) - 48)*10 + int(listArg[ ++str_it ]) - 48;
                cout << " heure : " << mesArgs.heure << endl;

                ++str_it;

            }
        }
        //}

        string verifType = "";
        do
        {
            verifType.clear();
            for(int i = 0 ; i < 4 && str_it + i <=  listArg.length() ; ++i)
            {
                verifType += listArg[ str_it + i];
            }

            mesArgs.nomLog += listArg[ str_it ];

            ++str_it;

        }while( verifType != ".log" && str_it < 1000);

        cout << mesArgs.nomLog + "log" << endl;
    }
    

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
