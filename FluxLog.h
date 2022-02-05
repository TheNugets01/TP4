/*************************************************************************
                           FluxLog  -  Permet de specialiser le flux ifstream pour nous permettre de lire une ligne
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe FluxLog (fichier FluxLog.h) ----------------
#if ! defined ( FLUXLOG_H )
#define FLUXLOG_H

//--------------------------------------------------- Interfaces utilisées

#include <fstream>
#include "Ligne.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <FluxLog>
// La classe FluxLog permet de specialiser le flux ifstream pour nous permettre de lire une ligne grace a une methode de la classe
//
//------------------------------------------------------------------------

class FluxLog : public ifstream
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    Ligne LireLigne();
    // Mode d'emploi
    // Construit un objet Ligne a partir d'une ligne du fichier de log

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    FluxLog(string nomFichier, ios_base::openmode mode);
    // Mode d'emploi
    // Construit l'objet FluxLog à partir du constructeur de ifstream

    ~FluxLog();
    // Mode d'emploi :
    // Détruit l'objet FluxLog
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <FluxLog>

#endif // FLUXLOG_H

