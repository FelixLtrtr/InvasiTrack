/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Déclaration de la classe Conservatoire
################################################
*/

#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <fstream>
#include ".nlohmann_3.11.3/json.hpp"

#include "utilisateur.hpp"

using namespace std;
using json = nlohmann::json;

class Conservatoire { // Classe conservatoire qui regroupe les utilisateurs et les espèces
    private:
        string nom;
        unordered_map<string, Utilisateur> utilisateurs;
        unordered_map<string, Espece> especes;
        string utilisateurConnecteId; // nécessaire pour retrouver l'utilisateur dans l'unoredered_map utilisateurs 

        // Gestion d'un utilisateur à la fois
        int suppr_utilisateur(); // suppression d'un utilisateur dans la map
        int creer_utilisateur();
        bool verifier_utilisateur(string id);


    public:
        Conservatoire(string nom, bool verbose = true){
            this -> nom = nom;
            this -> utilisateurConnecteId = "NULL";

            if (verbose) {cout << "Conservatoire " << nom << " créé.\n" << endl; }   
        };
        Conservatoire(){};
        ~Conservatoire(){};

        void set_Nom(string nom){this->nom = nom;}; 
        string get_Nom() {return this->nom;};

        void set_Utilisateurs(unordered_map<string, Utilisateur> utilisateurs){this->utilisateurs = utilisateurs;};
        unordered_map<string, Utilisateur> get_Utilisateurs(){return this->utilisateurs;};

        void set_Especes(unordered_map <string, Espece> especes){this->especes = especes;}; 
        unordered_map<string, Espece> get_Especes(){return this->especes;};

        string get_utilisateurConnecteId(){return this->utilisateurConnecteId;};
        void set_utilisateurConnecteId(string utilisateurConnecteId){this->utilisateurConnecteId = utilisateurConnecteId;}; 

        unique_ptr<Utilisateur> get_utilisateurConnecte();
        unique_ptr<Consultant> get_utilisateurConnecteConsultant();
        unique_ptr<Reporter> get_utilisateurConnecteReporter();

        int menu_connexion();
        int deconnexion();
        
        int menu_principal();
        int recherche_liste();
        int selection_recherche();
        
};

void verification_saisie_nombre(auto &saisie, string affichage_liste, int index_choix_min, int index_choix_max, string phrase_selection, bool afficher_menu, string menu, string conservatoire, string utilisateur, string type_utilisateur);