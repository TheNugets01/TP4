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
#include <vector>
#include <algorithm>

//------------------------------------------------------ Include personnel

#include "TraiterLog.h"

//------------------------------------------------------------- Constantes

typedef vector<string>::iterator vsit; // Iterateur de vecteur
typedef pair<string, int> site; // pair definissant un site et son nombre de hits
typedef list<site>::iterator lit; // Iterateur de list

#define TAILLELISTE 10 // Taille du Top 10

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

Arguments TraiterArgs(int nbArg, char *listArg[])
{
    Arguments mesArgs;

    if( nbArg == 1 )
    // Traitement de l'oublie du nom du fichier log à traiter
    {
        cerr << "l'appel à la fonction n'est pas bien formé" << endl;
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
        if( listArg[i][0] == '-' )
        {
            if( listArg[i][1] == 'g' && i+2 < nbArg ) // traitement du mode g
            {
                mesArgs.g = true;
                mesArgs.nomDot = listArg[++i];

                if ( mesArgs.nomDot.compare( mesArgs.nomDot.length()- 4 ,4,".dot") != 0 ) // Oublie de specifier le fichier dot
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
    list<site> top10; // Liste contenant le top 10
    lit itl; // Iterateur de liste

    for(umit itm = um.begin(); itm != um.end() ; ++itm) // On parcourt la map
    {
        if(top10.empty()) // Si la liste est vide on insere l'element
        {
            top10.push_front(*itm);
        }
        else
        {
            itl = --top10.end(); // On parcourt la liste a partir de la fin 
            if(top10.size()<TAILLELISTE) // Si la liste n'est pas pleine
            {
                while(itl != top10.begin() && itm->second > itl->second)
                { // on parcourt la liste tant que le nombre de hits est superieur
                    --itl;
                }
                if(itm->second < itl->second) //Quand on trouve un hit superieur on rebascule a la bonne position
                {
                    ++itl;
                }
                top10.insert(itl,*itm); // on insere dans le top 10
            }
            else // Si la liste est pleine
            {
                while(itl != top10.begin() && itm->second > itl->second)
                { // on parcourt la liste tant que le nombre de hit est superieur
                    --itl;
                }
                if(itl!=--top10.end()) // Si l'iterateur n'est pas positionne a la fin, il faut inserer une paire
                {
                    if(itl != top10.begin())
                    { // Si on est pas au debut de liste on insere a la position precedante
                        ++itl;
                        top10.insert(itl,*itm);
                        top10.erase(--top10.end()); // On pense a enlever la derniere paire
                    }
                    else
                    { // Si on est en debut de liste il faut verifier si l'on est plus grand ou plus petit que le premier
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
    for(itl = top10.begin(); itl != top10.end() ; ++itl) // A la fin on affiche le top 10
    {
       cout << "(" << itl->second <<" hits) " << itl->first  << endl;
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

    string urlInsa = "http://intranet-if.insa-lyon.fr"; // URL a enlever des referer

    string referer;
    string cible;
    int nbLink;
    int i;
    size_t found;
    bool inNodes;

    umit itCib;

    dest << "digraph {" << endl;

    for( umumit itRef = cptRefCib.begin() ; itRef != cptRefCib.end() ; ++itRef )
    { // on parcourt la map contenant les referer
        referer = itRef->first; // init referer
        found = referer.find( urlInsa ); //on cherche l'url insa
        if( found != string::npos )
        { // on la retire du referer
            referer = referer.erase(0 , urlInsa.length() );
        }
        else
        { // on ne prend que les referer contenant l'url insa
            continue;
        }

        if(referer.back() == '/')
        { // Si le referer fini par un / on l'enleve
            referer.pop_back();
        }

        i = 0;
        inNodes = false;
        while(!inNodes && i<Nodes.size())
        { // On parcourt la liste des noeuds pour verifier qu'il n'est pas deja present
            if(Nodes[i]==referer)
            { // s'il est present on retient sa position
                inNodes = true;
                posRef = i;
            }
            ++i;
        }
        if(!inNodes)
        { // sinon on l'ajoute au tableau et au fichier
            posRef = Nodes.size();
            Nodes.push_back(referer);
            dest << "node" << posRef << "[label=" << '"' << referer << '"' << "];" << endl;
        }

        for(umit itCib = itRef->second.begin() ; itCib!= itRef->second.end() ; ++itCib)
        { // pour chaque referer on parcourt les cibles qu'il atteint
            cible = itCib->first;
            hits = itCib->second;
            if(cible.back() == '/')
            { // idem on enleve le / a la fin
                cible.pop_back();
            }
            i = 0;
            inNodes = false;
            while(!inNodes && i<Nodes.size())
            { // On parcourt la liste des noeuds pour verifier que la cible n'est pas deja present
                if(Nodes[i]==cible)
                { // si elle est presente on retient sa position
                    inNodes = true;
                    posCib = i;
                }
                ++i;
            }
            if(!inNodes)
            { // sinon on l'ajoute au tableau et au fichier
                posCib = Nodes.size();
                Nodes.push_back(cible);
                dest << "node" << posCib << "[label=" << '"' << cible << '"' << "];" << endl;
            }
            // pour chaque cible on creer un lien avec son referer et le nombre de hits
            dest << "node" << posRef << " -> " << "node" << posCib << " [label=" << '"' << hits << '"' << "];" << endl;
        }
    }
    dest << '}';
}

void Analog(Arguments mesArgs)
{
    FluxLog src ( mesArgs.nomLog , ios_base::in);

    unordered_map< string , unordered_map<string,int> > cptRefCib; // une map contenant referer et cible pour le potentiel graph
    unordered_map<string,int> cptCible; // une autre contenant uniquement cible pour le top10

    FillUM(src , mesArgs , cptCible, cptRefCib ); // on rempli les maps
    Top10(cptCible); // on fait le top 10

    if(mesArgs.g)
    {
        Graph( cptRefCib , mesArgs.nomDot); // on fait le graph si demande
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

void FillUM( FluxLog & src , Arguments & mesArgs , umSI & cptCible ,umSumSI & cptRefCib)
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
    { // on parcourt chaque ligne du fichier jusqu'a la fin
        Ligne ligneCourante(src.LireLigne());

        httpCode = ligneCourante.GetHttpCode();
        cible = ligneCourante.GetCible();
        referer = ligneCourante.GetReferer();
        date = ligneCourante.GetDate();
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
        // Check des httpCode et des conditions de mode
        {
            if(mesArgs.g)
            //remplissage de la double UM si besoins
            {
                itref = cptRefCib.find(referer); // on cherche le referer

                if(itref == cptRefCib.end()) // si pas trouve on l'insere directement
                {
                    umSI m = {{cible,1}};
                    cptRefCib.insert({referer,m});
                }
                else
                { // si trouver on cherche la cible
                    itcib = itref->second.find(cible);

                    if(itcib == itref->second.end())
                    { // si cible pas trouver on l'insert
                        itref->second.insert({cible,1});
                    }
                    else
                    { // sinon on augmente son nombre de hits
                        itcib->second++;
                    }
                }
            }

            //Remplissage de cptCible pour le Top10
            itcib = cptCible.find(cible); // on cherche la cible

            if(itcib == cptCible.end())
            { // si pas trouver on l'insert
                cptCible.insert({cible,1});
            }
            else
            { // sinon on incremente son nombre de hits
                itcib->second++;
            }
        }
    }
}

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
