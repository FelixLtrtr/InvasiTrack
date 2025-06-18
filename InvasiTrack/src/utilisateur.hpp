/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Déclaration de la classe Utilisateur
################################################
*/

#include <iostream>
#include <cstring>
#include <memory> // pour utiliser les pointeurs intelligents

#include "espece.hpp"

using namespace std;

class Utilisateur {
    protected:
        string id;
        string mdp;
        string email;
        string type; // reporter ou consultant
    public:
        Utilisateur(){};
        Utilisateur(string id, string mdp, string email, string type, bool verbose = true){
            this->id = id;
            this->mdp = mdp;
            this->email = email;
            this->type = type;

            if (verbose) {cout << "Utilisateur " << id << " (" << type << ")" << " créé.\n" << endl; }
        };
        Utilisateur(string id, string mdp, string email){
            this->id = id;
            this->mdp = mdp;
            this->email = email;
        };
        ~Utilisateur(){};

        void set_Id(string id){this->id = id;};
        string get_Id(){return this->id;};

        void set_Mdp(string mdp){this->mdp = mdp;};
        string get_Mdp(){return this->mdp;};

        void set_Email(string email){this->email = email;};
        string get_Email(){return this->email;};

        void set_Type(string type){this->type = type;};
        string get_Type(){return this->type;};


        bool verifier_espece(string nom_espece, unordered_map<string, Espece> &especes);
        bool verifier_action(string nom_action, unordered_map<string, Action> &actions);
        bool nom_valide(string &nom_a_valider, string type_nom, bool selection_recherche, string verbe_menu);

        string selection_recherche(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes, string nom_espece_choisie, string menu);
        void verifier_date(int &jour, int &mois, int &annee, string type_date);
};


class Reporter : public Utilisateur {
    public:
        Reporter() : Utilisateur(id, mdp, email){};
        Reporter(string id, string mdp, string email, bool verbose = true) : Utilisateur(id, mdp, email){
            this->id = id;
            this->mdp = mdp;
            this->email = email;
            this->type = "reporter";

            if (verbose) {cout << "Utilisateur " << id << " (" << type << ")" << " créé.\n" << endl; }
        };
        ~Reporter(){};

        unique_ptr<Espece> ajouter_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes);
        int modifier_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes);
        int supprimer_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes);

        unique_ptr<Action> ajouter_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes);
        int modifier_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes);
        int supprimer_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes);

        FicheSuivi creer_ficheSuivi(string intituleAction, string typeAction, string idAuteur, vector<int> date, string lieu);
        int modifier_ficheSuivi(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes, string nom_action_choisie, unique_ptr<FicheSuivi> &fiche);
};

class Consultant : public Utilisateur {
    public:
        Consultant() : Utilisateur(id, mdp, email){};
        Consultant(string id, string mdp, string email, bool verbose = true) : Utilisateur(id, mdp, email){
            this->id = id;
            this->mdp = mdp;
            this->email = email;
            this->type = "consultant";

            if (verbose) {cout << "Utilisateur " << id << " (" << type << ")" << " créé.\n" << endl; }
        };
        ~Consultant(){};

        int consulter_action(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes);
        int consulter_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes);
        int cout_actions(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes);
        bool verifier_intervalle_temps(vector<int> &date_debut, vector<int> &date_cible, vector<int> &date_fin);
};

void verification_saisie_nombre_utilisateur(auto &saisie, string affichage_liste, int index_choix_min, int index_choix_max, string phrase_selection, bool afficher_menu, string menu, string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes, string nom_action_choisie);