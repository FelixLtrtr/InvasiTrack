/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Déclaration de la classe Action
################################################
*/

#include <iostream>
#include <cstring>
#include <vector>

#include "ficheSuivi.hpp"

using namespace std;

class Action {
    private:
        string intitule;
        string type; // Prévention, Surveillance, Intervention
        string espece;
        vector<int> date;
        string lieu;
        string idAuteur;
        string statut;
        string commentaires;
        FicheSuivi suivi;
        
    public:
        Action(string intitule, string type, string espece, vector<int> date, string lieu, string idAuteur, string statut, string commentaires, bool verbose = true){
            this->intitule = intitule;
            this->type = type;
            this->espece = espece;
            this->date = date;
            this->lieu = lieu;
            this->idAuteur = idAuteur;
            this->statut = statut;
            this->commentaires = commentaires;

            if (verbose){cout << "Action " << intitule << " créée.\n" << endl; }
        };

        Action(){};
        ~Action(){};
        
        void set_Intitule(string intitule){this->intitule = intitule;};
        string get_Intitule(){return this->intitule;};

        void set_Type(string type){this->type = type;};
        string get_Type(){return this->type;};

        void set_Espece(string espece){this->espece = espece;};
        string get_Espece(){return this->espece;};

        void set_Date(vector<int> date){this->date = date;};
        vector<int> get_Date(){return this->date;};

        void set_Lieu(string lieu){this->lieu = lieu;};
        string get_Lieu(){return this->lieu;};

        void set_IdAuteur(string idAuteur){this->idAuteur = idAuteur;};
        string get_IdAuteur(){return this->idAuteur;};

        void set_Statut(string statut){this->statut = statut;};
        string get_Statut(){return this->statut;};

        void set_Commentaires(string commentaires){this->commentaires = commentaires;}; 
        string get_Commentaires(){return this->commentaires;};

        void set_FicheSuivi(FicheSuivi suivi){this->suivi = suivi;};
        FicheSuivi get_FicheSuivi(){return this->suivi;};
};