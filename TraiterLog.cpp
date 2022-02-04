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

typedef vector<string>::iterator vsit;

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

void Top10( umSI & um)
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
       cout << '(' << itl->second << " hits) " << itl->first  << endl;
    }
    cout << endl;
}

void Graph( umSumSI cptRefCib , string nomDot )
{
    ofstream dest (nomDot);

    vector<string> Nodes;

    int posRef;
    int posCib;
    int hits;

    string urlInsa = "http://intranet-if.insa-lyon.fr";

    string referer;
    string cible;
    int nbLink;
    int i;

    size_t found;
    bool inNodes;

    umit itCib;

    dest << "digraph {" << endl;

    for( umumit itRef = cptRefCib.begin() ; itRef != cptRefCib.end() ; ++itRef )
    {
        referer = itRef->first; // init referer
        found = referer.find( urlInsa ); //formatage du referer sans l'url insa
        if( found != string::npos )
        {
            referer = referer.erase(0 , urlInsa.length() );
        }
        else
        {
            continue;
        }

        if(referer.back() == '/')
        {
            referer.pop_back();
        }

        i = 0;
        inNodes = false;
        while(!inNodes && i<Nodes.size())
        {
            if(Nodes[i]==referer)
            {
                inNodes = true;
                posRef = i;
            }
            ++i;
        }
        if(!inNodes)
        {
            posRef = Nodes.size();
            Nodes.push_back(referer);
            dest << "node" << posRef << "[label=" << '"' << referer << '"' << "];" << endl;
        }

        for(umit itCib = itRef->second.begin() ; itCib!= itRef->second.end() ; ++itCib)
        {
            cible = itCib->first;
            hits = itCib->second;
            if(cible.back() == '/')
            {
                cible.pop_back();
            }
            i = 0;
            inNodes = false;
            while(!inNodes && i<Nodes.size())
            {
                if(Nodes[i]==cible)
                {
                    inNodes = true;
                    posCib = i;
                }
                ++i;
            }
            if(!inNodes)
            {
                posCib = Nodes.size();
                Nodes.push_back(cible);
                dest << "node" << posCib << "[label=" << '"' << cible << '"' << "];" << endl;
            }
            dest << "node" << posRef << " -> " << "node" << posCib << " [label=" << '"' << hits << '"' << "];" << endl;
        }
    }
    dest << '}';
    cout << "fichier " << nomDot << " creer avec succes" << endl;
}

void Analog(Arguments mesArgs)
{
    FluxLog src ( mesArgs.nomLog , ios_base::in);

    if( mesArgs.g )
    {
        unordered_map< string , unordered_map<string,int> > cptLink;
        FillUM( cptLink , src , mesArgs);
        Graph( cptLink , mesArgs.nomDot);
    }
    else
    {
        unordered_map<string,int> cptLink;
        FillUM( cptLink , src , mesArgs);
    }
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

bool checkExtension( string cible )
{
    bool extensionType = true;
    size_t found;
    string unwantedExtension[] = { ".png" , ".jpg" , ".bmp" , ".gif" , ".css" , ".js"};
    int nbExtensions = 6;
    int i = 0;
    while (extensionType == true && i<nbExtensions)
    {
        found = cible.find(unwantedExtension[i]);
        if (found != string::npos) 
        {
            extensionType = false ;
        }
        ++i;
    }
    
    return extensionType;
}

void FillUM( umSI & cptCible , FluxLog & src , Arguments & mesArgs) //Sans Graph
{
    umit it;

    int httpCode;
    string cible;
    string date;
    int hLigne;

    bool chkTimes;
    bool extensionType;

    while(src.peek()!=EOF)
    {

        Ligne ligneCourante(src.LireLigne());
        httpCode = ligneCourante.httpCode;
        cible = ligneCourante.cible;
        date = ligneCourante.date;
        hLigne = stoi( date.erase(0,12).erase(2,12) );

        // -----Traitement du mode -t
        chkTimes = true;
        if( mesArgs.t )
        {
            chkTimes = checkTimes( hLigne , mesArgs.heure );
        }
        // -----Fin du traitement de -t
        
        // -----Traitement du mode -e
        extensionType = true;
        if( mesArgs.e )
        {
            extensionType = checkExtension( cible );
        }
        // -----Fin du traitement de -e

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
    }
    Top10(cptCible);
}

void FillUM( umSumSI & cptRefCib , FluxLog & src , Arguments & mesArgs) //Avec Graph
{
    umumit itref; // itérateur map contenant les refereur
    umit itcib; // itérateur map contenant les cibles

    int httpCode;
    string cible;
    string referer;
    string date;
    int hLigne;

    bool chkTimes;
    bool extensionType;

    while(src.peek()!=EOF)
    {
        Ligne ligneCourante(src.LireLigne());

        httpCode = ligneCourante.httpCode;
        cible = ligneCourante.cible;
        referer = ligneCourante.referer;
        date = ligneCourante.date;
        hLigne = stoi( date.erase(0,12).erase(2,12) );

        // -----Traitement du mode -t
        chkTimes = true;
        if( mesArgs.t )
        {
            chkTimes = checkTimes( hLigne , mesArgs.heure );
        }
        // -----Fin du traitement de -t

        // -----Traitement du mode -e
        extensionType = true;
        if( mesArgs.e )
        {
            extensionType = checkExtension( cible );
        }
        // -----Fin du traitement de -e

        if( (httpCode == 200 || httpCode == 304) && chkTimes && extensionType)
        //Check des httpCode et des conditions de mode
        {
            itref = cptRefCib.find(referer);

            if(itref == cptRefCib.end())
            {
                umSI m = {{cible,1}};
                cptRefCib.insert({referer,m});
            }
            else
            {
                itcib = itref->second.find(cible);

                if(itcib == itref->second.end())
                {
                    itref->second.insert({cible,1});
                }
                else
                {
                    itcib->second++;
                }
            }
        }
    }
}

void AfficherUM( umSI & um)
{
    for(umit it = um.begin(); it != um.end() ; ++it)
    {
        cout << '<' << it->first << ',' << it->second << '>' << endl;
    }
}

void AfficherUM(umSumSI & um)
{
    for(umumit it = um.begin(); it != um.end() ; ++it)
    {
        cout << it->first << " :"<< endl;
        for(umit it2 = it->second.begin(); it2 != it->second.end() ; ++it2)
        {
            cout << "   - " << '<' << it2->first << ',' << it2->second << '>' << endl;
        }
    }
}

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
