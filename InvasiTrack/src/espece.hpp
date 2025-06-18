/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Description du fichier
################################################
*/

#include <iostream>
#include <cstring>
#include <unordered_map>

#include "action.hpp"

using namespace std;

class Espece {
    private:
        string nom;
        string taxonomie;
        string categorieListe; // Alerte, Intérêt moindre , Observation, Espèces invasives
        string priorite; // Non-prioritaire, À surveiller, Prioritaire
        string cycleBiologique;
        string modeReproduction;
        string repartitionGeo;
        int nbIndividusRecenses;
        string voieIntroduction;
        string potentielDispersion; // Faible, Moyen, Important
        string impacts;
        string potentielInvasif; 
        string phaseInvasion; // Introduction, Installation, Expansion, Latence, Prolifération
        string commentaires;
        unordered_map<string, Action> actions;
    public:
        Espece(string nom, string taxonomie, string categorieListe, string priorite, string cycleBiologique, string modeReproduction, string repartitionGeo, int nbIndividusRecenses, string voieIntroduction, string potentielDispersion, string impacts, string potentielInvasif, string phaseInvasion, string commentaires, bool verbose = true){
            this->nom = nom;
            this->taxonomie = taxonomie;
            this->categorieListe = categorieListe;
            this->priorite = priorite;
            this->cycleBiologique = cycleBiologique;
            this->modeReproduction = modeReproduction;
            this->repartitionGeo = repartitionGeo;
            this->nbIndividusRecenses = nbIndividusRecenses;
            this->voieIntroduction = voieIntroduction;
            this->potentielDispersion = potentielDispersion;
            this->impacts = impacts;
            this->potentielInvasif = potentielInvasif;
            this->phaseInvasion = phaseInvasion;
            this->commentaires = commentaires;
     
            if (verbose){cout << "Espece " << nom << " créée.\n" << endl; }
        };
        
        Espece(){};
        ~Espece(){};

        void set_Nom(string nom){this-> nom = nom;};
        string get_Nom(){return this->nom;};

        void set_Taxonomie(string taxonomie){this-> taxonomie = taxonomie;};
        string get_Taxonomie(){return this->taxonomie;};

        void set_CategorieListe(string categorieListe){this-> categorieListe = categorieListe;};
        string get_CategorieListe(){return this->categorieListe;};

        void set_Priorite(string priorite){this-> priorite = priorite;};
        string get_Priorite(){return this->priorite;};

        void set_CycleBiologique(string cycleBiologique){this-> cycleBiologique = cycleBiologique;};
        string get_CycleBiologique(){return this->cycleBiologique;};

        void set_ModeReproduction(string modeReproduction){this-> modeReproduction = modeReproduction;};
        string get_ModeReproduction(){return this->modeReproduction;};

        void set_RepartitionGeo(string repartitionGeo){this-> repartitionGeo = repartitionGeo;};
        string get_RepartitionGeo(){return this->repartitionGeo;};

        void set_NbIndividusRecenses(int nbIndividusRecenses){this-> nbIndividusRecenses = nbIndividusRecenses;};
        int get_NbIndividusRecenses(){return this->nbIndividusRecenses;};

        void set_VoieIntroduction(string voieIntroduction){this-> voieIntroduction = voieIntroduction;};
        string get_VoieIntroduction(){return this->voieIntroduction;};

        void set_PotentielDispersion(string potentielDispersion){this-> potentielDispersion = potentielDispersion;};
        string get_PotentielDispersion(){return this->potentielDispersion;};

        void set_Impacts(string impacts){this-> impacts = impacts;};
        string get_Impacts(){return this->impacts;};

        void set_PotentielInvasif(string potentielInvasif){this-> potentielInvasif = potentielInvasif;};
        string get_PotentielInvasif(){return this->potentielInvasif;};

        void set_PhaseInvasion(string phaseInvasion){this-> phaseInvasion = phaseInvasion;};
        string get_PhaseInvasion(){return this->phaseInvasion;};

        void set_Commentaires(string commentaires){this-> commentaires = commentaires;};
        string get_Commentaires(){return this->commentaires;};

        void set_Actions(unordered_map<string, Action> actions){this-> actions = actions;};
        unordered_map<string, Action> get_Actions(){return this->actions;}; 
};