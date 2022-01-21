/*************************************************************************
                           LireLigne  -  Permet de lire une ligne du fichier log
                             -------------------
    début                : 14/01/2022
    copyright            : (C) 2022 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe LireLigne (fichier LireLigne.h) ----------------
#if ! defined ( LIRELIGNE_H )
#define LIRELIGNE_H

//--------------------------------------------------- Interfaces utilisées

#include <string>
#include <fstream>
#include "Ligne.h"
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LireLigne>
// La classe LireLigne va lire les informations d'une ligne du fichier log et créer une Ligne qui possède toutes les informations
//
//------------------------------------------------------------------------

class LireLigne : public ifstream
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    Ligne Lecture();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    LireLigne(string nomFichier, ios_base::openmode mode);
    // Mode d'emploi
    // Construit l'objet LireLigne à partir du constructeur de ifstream

    ~LireLigne();
    // Mode d'emploi :
    // Détruit l'objet LireLigne
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <LireLigne>

#endif // LIRELIGNE_H

