/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Déclaration de la classe Accueil
################################################
*/

#include <iostream>
#include <unordered_map>
#include <cstring>
#include ".nlohmann_3.11.3/json.hpp"
#include <memory> // pour utiliser les pointeurs intelligents

#include "conservatoire.hpp"

using namespace std;
using json = nlohmann::json;

class Accueil {
    private:
        unordered_map<string, Conservatoire> conservatoires;
        string conservatoireSelectionneNom;
    public:
        Accueil(){
            this -> conservatoireSelectionneNom = "NULL";
        };
        ~Accueil(){};

        void set_Conservatoires(unordered_map<string, Conservatoire> conservatoires){this->conservatoires = conservatoires;};
        unordered_map<string, Conservatoire> get_Conservatoires(){return this->conservatoires;};

        void set_ConservatoireSelectionneNom(string conservatoireSelectionneNom){this->conservatoireSelectionneNom = conservatoireSelectionneNom;};
        string get_ConservatoireSelectionneNom(){return this->conservatoireSelectionneNom;};

        void choix_conservatoire();

        unique_ptr<Conservatoire> get_ConservatoireSelectionne();

};