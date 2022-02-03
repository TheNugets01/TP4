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


#include "TraiterLog.h"

//------------------------------------------------------------- Constantes
typedef unordered_map<string,int> umSI;
typedef unordered_map<string,int>::iterator umit;

typedef unordered_map<string , unordered_map<string,int>> umSumSI;
typedef unordered_map<string , unordered_map<string,int>>::iterator umumit ;

typedef pair<string, int> site;
typedef list<site>::iterator lit;
#define TAILLELISTE 10

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

    mesArgs.nomLog = listArg[nbArg - 1];
    if ( mesArgs.nomLog.length() <= 4 || mesArgs.nomLog.compare( mesArgs.nomLog.length()- 4 ,4,".log") != 0 )
    {
        cerr << "Erreur ! Le fichier '.log' est mal définie ou mal positionné!" << endl;
        cerr << "----Pensez à bien spécifiez le type '.log' et d'écrire le nom de fichier à la fin" << endl;
        mesArgs.g = false;
        mesArgs.e = false;
        mesArgs.t = false;
        mesArgs.nomDot = "";
        mesArgs.nomLog = "";
        mesArgs.heure = -1;
    }

    for(int i = 1 ; i < nbArg - 1 ; ++i) // traitement des modes si il y en a
    {
        //cout << listArg[i] << endl;

        if( listArg[i][0] == '-' )
        {
            if( listArg[i][1] == 'g' && i+2 < nbArg ) // traitement du mode g
            {
                mesArgs.g = true;
                mesArgs.nomDot = listArg[++i];

                if ( mesArgs.nomDot.compare( mesArgs.nomDot.length()- 4 ,4,".dot") != 0 )
                {
                    cerr << "Erreur ! Le fichier '.dot' est mal définie !" << endl;
                    cerr << " ---------Pensez à bien spécifiez le type '.dot' " << endl;
                    mesArgs.g = false;
                    mesArgs.nomDot = "";
                }
            }
            else if ( listArg[i][1] == 'e' && i+1 < nbArg ) // traitement du mode e
            {
                mesArgs.e = true;
            }
            else if ( listArg[i][1] == 't' && i+2 < nbArg ) // traitement du mode t
            {
                mesArgs.t = true;
                mesArgs.heure = stoi(listArg[++i]);
            }
            else
            {
                cerr << "Erreur ! Un des modes n'est pas connu ou est mal défini !" << endl;
                return mesArgs;
            }
        }
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
    list<site> top10;
    lit itl;

    for(umit itm = um.begin(); itm != um.end() ; ++itm)
    {
        if(top10.empty())
        {
            top10.push_front(*itm);
        }
        else
        {
            itl = --top10.end();
            if(top10.size()<TAILLELISTE)
            {
                while(itl != top10.begin() && itm->second > itl->second)
                {
                    --itl;
                }
                if(itm->second < itl->second)
                {
                    ++itl;
                }
                top10.insert(itl,*itm);
            }
            else
            {
                while(itl != top10.begin() && itm->second > itl->second)
                {
                    --itl;
                }
                if(itl!=--top10.end())
                {
                    if(itl != top10.begin())
                    {
                        ++itl;
                        top10.insert(itl,*itm);
                        top10.erase(--top10.end());
                    }
                    else
                    {
                        if(itm->second < itl->second)
                        {
                            ++itl;
                        }
                        top10.insert(itl,*itm);
                        top10.erase(--top10.end());
                    }
                }
            }
        }
    }
    for(itl = top10.begin(); itl != top10.end() ; ++itl)
    {
       cout << itl->second << " : " << itl->first  << endl;
    }
    cout << endl;
}

void Analog(Arguments mesArgs)
{
    FluxLog src ( mesArgs.nomLog , ios_base::in);
    
    if( mesArgs.g )
    {
        unordered_map< string , unordered_map<string,int> > cptLink;
        FillUM( cptLink , src , mesArgs);
    }
    else
    {
        unordered_map<string,int> cptLink;
        FillUM( cptLink , src , mesArgs);
    }
    
    //FillUM( cptLink , src , mesArgs);
    
    
    
    
    
    //FluxLog src ("test.log", ios_base::in);
    //int i = 0;
    /*unordered_map<string,int> cptCible;

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
        //i++;
    }
    //AfficherUM(cptCible);
    Top10(cptCible);*/
}

bool checkTimes( int hLigne , int hCond)
{
    bool checkTimes = true;
    if( hLigne != hCond )
    {
        checkTimes = false;
    }

    return checkTimes;
} 

void FillUM( umSI & cptCible , FluxLog & src , Arguments & mesArgs) //Sans Graph
{
    while(src.peek()!=EOF)
    {
        umit it;
        Ligne ligneCourante(src.LireLigne());

        int httpCode = ligneCourante.httpCode;
        string cible = ligneCourante.cible;
        string date = ligneCourante.date;
        int hLigne = stoi( date.erase(0,12).erase(2,12) );

        // -----Traitement du mode -t
        bool chkTimes = true;
        bool extensionType = true;
        if( mesArgs.t )
        {
            chkTimes = checkTimes( hLigne , mesArgs.heure );
        }
        // -----Fin du traitement de -t
        
        // TRAITEMENT DU MODE -e
        /*if( mesArgs.e )
        {
            string unwantedExtension [] = { ".png" , ".jpg" , ".bmp" , ".gif" , ".css" , ".js "}; 
            int sizeTab = sizeof(unwantedExtension)/sizeof(unwantedExtension[0]);

            for(int i = 0; i < cible.length()-4 ; ++i)
            {
                for(int j = 0 ; j < sizeTab ; ++j)
                {
                    if( cible.compare( i ,4,unwantedExtension[j]) == 0 )
                    {
                        extensionType = false;
                    }
                }
            }
        }*/

        if( (httpCode == 200 || httpCode == 304) && chkTimes && extensionType)
        //Check des httpCode et des conditions de mode
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

        //cout << mesArgs.heure << "/" << heureLigne << ":" << chekTimes << endl;
    }
    //AfficherUM(cptCible);
    Top10(cptCible);
}

void FillUM( umSumSI & cptRefCib , FluxLog & src , Arguments & mesArgs) //Avec Graph
{

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
