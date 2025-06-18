/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Déclaration de la classe FicheSuivi
################################################
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class FicheSuivi {
    private :
        string intituleAction;
        string typeAction;
        string idAuteur;
        vector<int> date;
        string lieu;
        string acteurs;
        string materiel;    
        float coutAction;
        string financement;
        string descriptif;

    public :
        FicheSuivi(string intituleAction, string typeAction, string idAuteur, string descriptif, vector<int> date, string lieu, string acteurs, string materiel, float coutAction, string financement, bool verbose = true){
            this->intituleAction = intituleAction;
            this->typeAction = typeAction;
            this->idAuteur = idAuteur;
            this->descriptif = descriptif;
            this->date = date;
            this->lieu = lieu;
            this->acteurs = acteurs;
            this->materiel = materiel;
            this->coutAction = coutAction;
            this->financement = financement;

            if (verbose){cout << "Fiche de suivi de l'action " << intituleAction << " créée.\n" << endl; }
        };
        FicheSuivi(string intituleAction, bool verbose = true){
            this->intituleAction = intituleAction;

            if (verbose){cout << "Fiche de suivi de l'action " << intituleAction << " créée.\n" << endl; }
        }
        FicheSuivi(){};
        ~FicheSuivi(){};

        void set_IntituleAction(string intituleAction){this->intituleAction = intituleAction;};
        string get_IntituleAction(){return this->intituleAction;};

        void set_TypeAction(string typeAction){this->typeAction = typeAction;};
        string get_TypeAction(){return this->typeAction;};

        void set_IdAuteur(string idAuteur){this->idAuteur = idAuteur;};
        string get_IdAuteur(){return this->idAuteur;};

        void set_Descriptif(string descriptif){this->descriptif = descriptif;};
        string get_Descriptif(){return this->descriptif;};

        void set_Date(vector<int> date){this->date = date;};
        vector<int> get_Date(){return this->date;};

        void set_Lieu(string lieu){this->lieu = lieu;};
        string get_Lieu(){return this->lieu;};

        void set_Acteurs(string acteurs){this->acteurs = acteurs;};
        string get_Acteurs(){return this->acteurs;};

        void set_Materiel(string materiel){this->materiel = materiel;};
        string get_Materiel(){return this->materiel;};

        void set_CoutAction(float coutAction){this->coutAction = coutAction;};
        float get_CoutAction(){return this->coutAction;};

        void set_Financement(string financement){this->financement = financement;};
        string get_Financement(){return this->financement;};

};